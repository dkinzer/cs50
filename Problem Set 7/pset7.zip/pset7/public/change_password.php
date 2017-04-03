<?php

    // configuration
    require("../includes/config.php"); 

    // if user reached page via GET (as by clicking a link or via redirect)
    if ($_SERVER["REQUEST_METHOD"] == "GET")
    {
        // else render form
        render("change_password_form.php", ["title" => "Change Password"]);
    }

    // else if user reached page via POST (as by submitting a form via POST)
    else if ($_SERVER["REQUEST_METHOD"] == "POST")
    {
        // validate submission
        if (empty($_POST["password"]))
        {
            apologize("You must provide your password.");
        }
        if (empty($_POST["confirmation"]))
        {
            apologize("You must provide the confirmation password.");
        }
        if ($_POST["confirmation"] != $_POST["password"])
        {
            apologize("Confirmation password does not equal password.");
        }

        // query database for user
        $hash = password_hash($_POST["password"], PASSWORD_DEFAULT);
        CS50::query("UPDATE users SET hash = ? WHERE id = ?", $hash, $_SESSION["id"]);
        redirect("/");
    }

?>
