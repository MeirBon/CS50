<?php

    require(__DIR__ . "/../includes/config.php");

    // numerically indexed array of places
    $places = [];

    // search database for places matching $_GET["geo"], store in $places
    // first search if full match
    $places = CS50::query("SELECT * FROM places WHERE MATCH(country_code, postal_code, place_name, admin_name1, admin_code1) AGAINST (?) LIMIT 20", $_GET["geo"]);
    
    // if no matches where found, try to find suggestions
    if (empty($places))
    {
        $places = CS50::query("SELECT * FROM places WHERE (postal_code) LIKE (?) OR (place_name) LIKE (?) LIMIT 20", $_GET["geo"] . "%", $_GET["geo"] . "%");
    }

    // output places as JSON (pretty-printed for debugging convenience)
    header("Content-type: application/json");
    print(json_encode($places, JSON_PRETTY_PRINT));

?>