<?php

    // configuration
    require("../includes/config.php"); 
    $history = CS50::query("SELECT * FROM history WHERE users_id = ?", $_SESSION["id"]);

    // render portfolio
    render("history.php", ["title" => "History", "history" => $history]);

?>
