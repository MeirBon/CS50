<?php

    // configuration
    require("../includes/config.php");
    
    // if user reached page via GET (as by clicking a link or via redirect)
    if ($_SERVER["REQUEST_METHOD"] == "GET")
    {
        // get user cash
        $userinfo = CS50::query("SELECT cash FROM users WHERE id = ?", $_SESSION["id"]);
        
        // user has no money
        if ($userinfo[0]["cash"] < 10)
        {
            render("job.php", ["title" => "Buy"]);
        }
        else
        {
            // else render form
            render("buy_form.php", ["title" => "Buy"]);
        }
    }
    
    else if ($_SERVER["REQUEST_METHOD"] == "POST")
    {
        // no input
        if ($_POST["symbol"] == NULL || $_POST["shares"] == NULL)
        {
            apologize("Please enter a symbol and quantity of shares to buy.");
        }
        // if company is not found
        else if (!lookup($_POST["symbol"]))
        {
            apologize("Symbol is invalid.");
        }
        
        // remember the kind of transaction
        $transaction = "Bought";
        
        // lookup stock
        $stock = lookup($_POST["symbol"]);
        
        // get user's cash
        $cash = CS50::query("SELECT cash FROM users WHERE id = ?", $_SESSION["id"]);
        
        // calculate cost
        $cost = $_POST["shares"] * $stock["price"];
        
        // make sure user does not buy too much
        if ($cost > $cash[0]["cash"])
        {
            apologize("You can't afford that.");
        }
        else
        {
            $_POST["symbol"] = strtoupper($_POST["symbol"]);
            
            CS50::query("INSERT INTO portfolios (user_id, symbol, shares) VALUES (?, ?, ?) ON DUPLICATE KEY UPDATE shares = shares + VALUES(shares)", $_SESSION["id"], $_POST["symbol"], $_POST["shares"]);
            
            // update cash
            CS50::query("UPDATE users SET cash = cash - ? WHERE id = ?", $cost, $_SESSION["id"]);
            
            // remember the transaction
            CS50::query("INSERT INTO history (user_id, transaction, symbol, shares, price) VALUES (?, ?, ?, ?, ?)", $_SESSION["id"], $transaction, $_POST["symbol"], $_POST["shares"], $stock["price"]);
            
            // redirect to portfolio
            redirect("/");
        }
    }
    else
    {
        // if anything goes wrong
        apologize("Something went wrong, please try again.");
    }
?>