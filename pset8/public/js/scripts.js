/* global google */
/* global _ */
/**
 * scripts.js
 *
 * Computer Science 50
 * Problem Set 8
 * 
 * Meir Noordermeer
 *
 * Global JavaScript.
 */

// Google Map
var map;

// markers for map
var markers = [];

// info window
var info = new google.maps.InfoWindow();

// execute when the DOM is fully loaded
$(function() {

    // styles for map
    // https://developers.google.com/maps/documentation/javascript/styling
    var styles = [

        // hide Google's labels
        {
            featureType: "all",
            elementType: "labels",
            stylers: [
                {visibility: "off"}
            ]
        },

        // hide roads
        {
            featureType: "road",
            elementType: "geometry",
            stylers: [
                {visibility: "off"}
            ]
        }
    ];

    // options for map
    // https://developers.google.com/maps/documentation/javascript/reference#MapOptions
    var options = {
        center: {lat: 37.4236, lng: -122.1619}, // Stanford, California
        disableDefaultUI: true,
        mapTypeId: google.maps.MapTypeId.ROADMAP,
        maxZoom: 14,
        panControl: true,
        styles: styles,
        zoom: 13,
        zoomControl: true
    };

    // get DOM node in which map will be instantiated
    var canvas = $("#map-canvas").get(0);

    // instantiate map
    map = new google.maps.Map(canvas, options);

    // configure UI once Google Map is idle (i.e., loaded)
    google.maps.event.addListenerOnce(map, "idle", configure);

});

/**
 * Adds marker for place to map.
 */
function addMarker(place)
{
    // create marker
    var marker = new MarkerWithLabel({
        icon: "https://maps.google.com/mapfiles/kml/pal2/icon23.png",
        position: new google.maps.LatLng(place.latitude, place.longitude),
        map: map,
        labelContent: place.place_name + ", " + place.admin_name1,
        labelAnchor: new google.maps.Point(20, 0),
        labelClass: "labels", // the CSS class for the label
        labelStyle: {opacity: 0.75}
    }); 

    // add event listener when marker is clicked
    google.maps.event.addListener(marker, "click", function() {
        
        // show empty info window
        showInfo(marker);
        
        // get the articles based on postal code
        $.getJSON("articles.php", "geo=" + place.postal_code + "," + place.place_name)
        
        // when getJSON is done
        .done(function(data, textStatus, jqXHR)
        {
            // when no news available
            if (data.length == 0)
            {
                // inform user
                showInfo(marker, "Sorry, no news available.");
            }
            // when news is available
            else
            {
                // generate html
                var info = htmlgen(place.place_name, place.admin_name1, data, place.accuracy);
                
                // show infowindow
                showInfo(marker, info);
            }
        });
    });    
    
    // add the marker to the global array of markers
    markers.push(marker);
}
/**
 * Generates html formatted unordered list 
 */
function htmlgen(placename, adminname, data, size)
{
    // add search arguments
    var search = placename + ",+" + adminname;
    
    // set news list size
    var max_size = size * 5;
    
    // convert search string to be compatible with wikipedia
    for (var i = 0; i < search.length; i++)
    {
        // check for space
        if (search[i] == " ")
        {
            search[i] = '+';
        }
    }
    
    // create wikipedia search
    var info = "<p id='wikisearch'>Click <a href='https://en.wikipedia.org/w/index.php?search=" + search + "'" + ">here</a> to search for this location on wikipedia.</p>";
    
    // start list
    info += "<ul>";

    // (re)set i to 0
    var i = 0;
    
    // if size is 0 make list size of amount of items (or if something went wrong)
    if (!max_size || max_size == 0)
    {
        while (i < data.length)
        {
            // add list item
            info += "<li><a href='" + data[i].link + "'>" + data[i].title + "</a>'</li>";
        
            // set next index
            i++;
        }
    }
    // otherwise max items of size
    else
    {
        while (i < data.length && i < max_size)
        {
            // add list item
            info += "<li><a href='" + data[i].link + "'>" + data[i].title + "</a>'</li>";
        
            // set next index
            i++;
        }
    }
    
    // end the list
    info += "</ul>";

    return info;
}
/**
 * Configures application.
 */
function configure()
{
    // update UI after map has been dragged
    google.maps.event.addListener(map, "dragend", function() {
        update();
    });

    // update UI after zoom level changes
    google.maps.event.addListener(map, "zoom_changed", function() {
        update();
    });

    // remove markers whilst dragging
    google.maps.event.addListener(map, "dragstart", function() {
        removeMarkers();
    });

    // configure typeahead
    // https://github.com/twitter/typeahead.js/blob/master/doc/jquery_typeahead.md
    $("#q").typeahead({
        autoselect: true,
        highlight: true,
        minLength: 1
    },
    {
        source: search,
        templates: {
            empty: "no places found yet",
            suggestion: _.template("<p><%- place_name %>, <%- admin_name1 %>, <%- postal_code %></p>")
        }
    });

    // re-center map after place is selected from drop-down
    $("#q").on("typeahead:selected", function(eventObject, suggestion, name) {

        // ensure coordinates are numbers
        var latitude = (_.isNumber(suggestion.latitude)) ? suggestion.latitude : parseFloat(suggestion.latitude);
        var longitude = (_.isNumber(suggestion.longitude)) ? suggestion.longitude : parseFloat(suggestion.longitude);

        // set map's center
        map.setCenter({lat: latitude, lng: longitude});

        // update UI
        update();
    });

    // hide info window when text box has focus
    $("#q").focus(function(eventData) {
        hideInfo();
    });

    // re-enable ctrl- and right-clicking (and thus Inspect Element) on Google Map
    // https://chrome.google.com/webstore/detail/allow-right-click/hompjdfbfmmmgflfjdlnkohcplmboaeo?hl=en
    document.addEventListener("contextmenu", function(event) {
        event.returnValue = true; 
        event.stopPropagation && event.stopPropagation(); 
        event.cancelBubble && event.cancelBubble();
    }, true);

    // update UI
    update();

    // give focus to text box
    $("#q").focus();
}

/**
 * Hides info window.
 */
function hideInfo()
{
    info.close();
}

/**
 * Removes markers from map.
 */
function removeMarkers()
{
    // loop through all the markers
    for (var i = 0, n = markers.length; i < n; i++)
    {
        // set marker to null
        markers[i].setMap(null);
    }
    
    //reset markers length
    markers.length = 0;
}

/**
 * Searches database for typeahead's suggestions.
 */
function search(query, cb)
{
    // get places matching query (asynchronously)
    var parameters = {
        geo: query
    };
    $.getJSON("search.php", parameters)
    .done(function(data, textStatus, jqXHR) {

        // call typeahead's callback with search results (i.e., places)
        cb(data);
    })
    .fail(function(jqXHR, textStatus, errorThrown) {

        // log error to browser's console
        console.log(errorThrown.toString());
    });
}

/**
 * Shows info window at marker with content.
 */
function showInfo(marker, content)
{
    // start div
    var div = "<div id='info'>";
    if (typeof(content) === "undefined")
    {
        // http://www.ajaxload.info/
        div += "<img alt='loading' src='img/ajax-loader.gif'/>";
    }
    else
    {
        div += content;
    }

    // end div
    div += "</div>";

    // set info window's content
    info.setContent(div);

    // open info window (if not already open)
    info.open(map, marker);
}

/**
 * Updates UI's markers.
 */
function update() 
{
    // get map's bounds
    var bounds = map.getBounds();
    var ne = bounds.getNorthEast();
    var sw = bounds.getSouthWest();

    // get places within bounds (asynchronously)
    var parameters = {
        ne: ne.lat() + "," + ne.lng(),
        q: $("#q").val(),
        sw: sw.lat() + "," + sw.lng()
    };
    $.getJSON("update.php", parameters)
    .done(function(data, textStatus, jqXHR) {

        // remove old markers from map
        removeMarkers();

        // add new markers to map
        for (var i = 0; i < data.length; i++)
        {
            addMarker(data[i]);
        }
     })
     .fail(function(jqXHR, textStatus, errorThrown) {

         // log error to browser's console
         console.log(errorThrown.toString());
     });
}