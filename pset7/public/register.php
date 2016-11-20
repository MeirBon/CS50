<?php

    // configuration
    require("../includes/config.php");

    // if user reached page via GET (as by clicking a link or via redirect)
    if ($_SERVER["REQUEST_METHOD"] == "GET")
    {
        // else render form
        render("register_form.php", ["title" => "Register"]);
    }

    // else if user reached page via POST (as by submitting a form via POST)
    else if ($_SERVER["REQUEST_METHOD"] == "POST")
    {
        // check username
        if ($_POST["username"] == NULL)
        {
            apologize("Please fill in a valid username.");
        }
        // check password
        else if ($_POST["password"] == NULL)
        {
            apologize("Please fill in a valid username.");
        }
        // check if passwords match
        else if($_POST["password"] != $_POST["confirmation"])
        {
            apologize("Passwords did not match.");
        }
        else
        {
            // create username
            if (CS50::query("INSERT IGNORE INTO users (username, hash, cash) VALUES(?, ?, 10000.0000)", $_POST["username"], password_hash($_POST["password"], PASSWORD_DEFAULT)))
            {
                // get user id
                $rows = CS50::query("SELECT LAST_INSERT_ID() AS id");
                $id = $rows[0]["id"];

                // remember that user's now logged in by storing user's ID in session
                $_SESSION["id"] = $id;

                // redirect to portfolio
                redirect("/");
            }
            // if query returned 0
            else
            {
                // username is already in use
                apologize("The given username is already in use.");
            }
        }
    }
    
    // if anything goes wrong, apologize
    apologize("Something went wrong, please try again.");
?>