<?php

    // configuration
    require("../includes/config.php");
    
    // if user reached page via GET (as by clicking a link or via redirect)
    if ($_SERVER["REQUEST_METHOD"] == "GET")
    {
        // else render form
        render("quote_form.php", ["title" => "Quote"]);
    }
    
    // if user submitted
    else if ($_SERVER["REQUEST_METHOD"] == "POST")
    {
        // make sure proper usage
        if ($_POST["symbol"] == NULL)
        {
            apologize("Please enter a symbol.");
        }
        // look up symbol
        else
        {
            // look up stock (returns associative array of: 'symbol'; 'name'; 'price')
            $stock = lookup($_POST["symbol"]);
            
            // symbol not found
            if ($stock["symbol"] == NULL)
            {
                apologize("Symbol not found.");
            }
            
            // render page for user
            render("quote.php", ["title" => "Quote", "price" => $stock["price"], "name" => $stock["name"], "symbol" => $stock["symbol"]]);
        }
    }
    else
    {
        apologize("Something went wrong, please try again.");
    }
?>