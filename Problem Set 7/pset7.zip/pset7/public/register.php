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
        // validate submission
        if (empty($_POST["username"]))
        {
            apologize("You must provide a username.");
        }
        else if (empty($_POST["password"]) || empty($_POST["confirmation"]))
        {
            apologize("You must provide both the password and its confirmation.");
        }
        else if (empty($_POST["password"]) || empty($_POST["confirmation"]))
        {
            apologize("You must provide both the password and its confirmation.");
        }
        else if (empty($_POST["password"]) != empty($_POST["confirmation"]))
        {
            apologize("Your password and confirmation are not equal.");
        }

        $rows = CS50::query("SELECT * FROM users WHERE username = ?", $_POST["username"]);
        if (count($rows) == 1)
        {
            apologize("That username is taken.");
        }
        else {
            CS50::query("INSERT INTO users (username, cash, hash) VALUES (?, ?, ?)", $_POST["username"],
                1000.0000, password_hash($_POST["password"], PASSWORD_DEFAULT));
            $row = CS50::query("SELECT LAST_INSERT_ID() as id");

            // remember that user's now logged in by storing user's ID in session
            $_SESSION["id"] = $row[0]['id'];

            // redirect to portfolio
            redirect("/");
        }

    }

?>
