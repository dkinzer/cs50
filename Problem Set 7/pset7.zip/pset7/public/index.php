<?php

    // configuration
    require("../includes/config.php"); 

    $positions = user_get_positions($_SESSION['id']);
    $cash = user_get_cash($_SESSION['id']);

    // render portfolio
    render("portfolio.php", ["title" => "Portfolio", "positions" => $positions, "cash" => $cash]);

?>
