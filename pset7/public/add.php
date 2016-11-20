<?php

    // configuration
    require("../includes/config.php");
    
    // render form to user
    if ($_SERVER["REQUEST_METHOD"] == "GET")
    {
        render("add_form.php", ["title" => "Buy"]);
    }
    // update user's cash
    else if ($_SERVER["REQUEST_METHOD"] == "POST")
    {
        // update user's cash
        CS50::query("UPDATE users SET cash = cash + ? WHERE id = ?", $_POST["amount"], $_SESSION["id"]);
        
        // redirect to buy
        redirect("/buy.php");
    }
    // if anything weird happens
    else
    {
        render("add_form.php", ["title" => "Add"]);
    }
?>