<?php

    // configuration
    require("../includes/config.php");
    
    // if user reached page via GET (as by clicking a link or via redirect)
    if ($_SERVER["REQUEST_METHOD"] == "GET")
    {
        // generate options
        $options = CS50::query("SELECT symbol FROM portfolios WHERE user_id = ?", $_SESSION["id"]);
        
        // apologize if there is nothing to sell
        if ($options == NULL)
        {
            apologize("Nothing to sell");
        }
        
        // else render form
        render("sell_form.php", ["title" => "Sell", "options" => $options]);
    }
    
    else if ($_SERVER["REQUEST_METHOD"] == "POST")
    {
        // initialize sell_all variable
        $sell_all = FALSE;
        
        // query amount of stocks user has
        $user = CS50::query("SELECT * FROM portfolios WHERE user_id = ? AND symbol = ?", $_SESSION["id"], $_POST["symbol"]);
        
        // check if user selected a symbol
        if (empty($_POST["symbol"]))
        {
            apologize("Please select a symbol.");
        }
        if (!is_numeric($_POST["shares"]))
        {
            if ($_POST["shares"] == "all")
            {
                $sell_all = TRUE;
            }
            else
            {
                apologize("Please enter a numeric value or 'all' to sell all shares of this symbol.");
            }
        }
        else
        {
            // make sure user does not oversell
            if ($user[0]["shares"] < $_POST["shares"])
            {
                apologize("You don't have that many shares.");
            }
        }
        
        // remember the kind of transaction
        $transaction = "Sold";

        // look up stock
        $stock = lookup($_POST["symbol"]);

        // if user wants to sell all
        if ($user[0]["shares"] == $_POST["shares"] || $sell_all)
        {
            $sold = $stock["price"] * $user[0]["shares"];
            
            // sell the stocks
            CS50::query("DELETE FROM portfolios WHERE user_id = ? AND symbol = ?",$_SESSION["id"], $_POST["symbol"]);
            
            // add money back to user portfolio
            CS50::query("UPDATE users SET cash = cash + ? WHERE id = ?", $sold, $_SESSION["id"]);
        
            // remember the transaction
            CS50::query("INSERT INTO history (user_id, transaction, symbol, shares, price) VALUES (?, ?, ?, ?, ?)", $_SESSION["id"], $transaction, $_POST["symbol"], $user[0]["shares"], $stock["price"]);
        
            // redirect to portfolio
            redirect("/");
        }
        else
        {
            $sold = $stock["price"] * $_POST["shares"];
            
            CS50::query("UPDATE portfolios SET shares = shares - ? WHERE user_id = ? AND symbol = ? ", $_POST["shares"], $_SESSION["id"], $_POST["symbol"]);
            
            // add money back to user portfolio
            CS50::query("UPDATE users SET cash = cash + ? WHERE id = ?", $sold, $_SESSION["id"]);
            
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