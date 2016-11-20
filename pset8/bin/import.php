#!/usr/bin/env php
<?php

    /**
     * import.php
     * 
     * Programmeren 2
     * Problem Set 8
     * 
     * <Meir Noordermeer (11341335)
     * 
     * Imports a file from GeoNames given by the user into the SQL database.
     **/
    
    // configuration
    require("../includes/config.php");
    
    // (re)set counter
    $counter = 0;
    
    //check proper usage
    if ($argc == 1)
    {
        print("Please give the file you want to import as a command-line argument.\n");
        exit(1);
    }

    // open file
    $file = fopen($argv[1], "r");
    
    // check if opened
    if ($file)
    {
        // check if file is readable
        if (!is_readable($argv[1]))
        {
	        print("Unable to read file.");
	        exit(1);
        }

        // iterate over lines
        while($file = fgetcsv($file, 0, "\t"))
        {
            // insert information into database
            CS50::query("INSERT INTO places (country_code, postal_code, place_name, admin_name1, admin_code1, admin_name2, 
            admin_code2, admin_name3, admin_code3, latitude, longitude, accuracy) 
            VALUES (?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?)", 
            $file[0], $file[1], $file[2], $file[3], $file[4], $file[5], 
            $file[6], $file[7], $file[8], $file[9], $file[10], $file[11]);
            
            $counter++;
        }
    }
    else
    {
        print("Unable to open file.");
        exit(2);
    }
    
    // inform user program was successful and the count of the inserted objects
    printf("%d Objects inserted.\n", $counter);
    
    // close file
    fclose($file);
?>