<?php
    
    // configuration
    require("../includes/config.php"); 

    // user wants to clear history
    if ($_SERVER["REQUEST_METHOD"] == "POST")
    {
        // delete entries
        CS50::query("DELETE FROM history WHERE user_id = ?",$_SESSION["id"]);
        
        // render portfolio
        render("history.php", ["title" => "History"]);
    }
    // render page
    else
    {
        // render portfolio
        render("history.php", ["title" => "History"]);
    }
?>
