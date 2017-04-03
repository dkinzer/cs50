<?php
    // configuration
    require("../includes/config.php");
    $positions = user_get_positions($_SESSION["id"]);

    if (count($positions) == 0)
    {
        apologize("Nothing to sell.");
    }

    // if user reached page via GET (as by clicking a link or via redirect)
    if ($_SERVER["REQUEST_METHOD"] == "GET")
    {
        // render portfolio
        render("sell_form.php", ["title" => "Portfolio", "positions" => $positions]);
    }

    // else if user reached page via POST (as by submitting a form via POST)
    else if ($_SERVER["REQUEST_METHOD"] == "POST")
    {
        if (isset($positions[$_POST["sell-symbol"]]))
        {
            $asset = $positions[$_POST["sell-symbol"]];
            $stock = lookup($_POST["sell-symbol"]);
            $cash = $stock["price"] * $asset["shares"];
            $action = [
                "transaction_type" => "SELL",
                "user_id" => $_SESSION["id"],
                "symbol" => $stock["symbol"],
                "price" => $stock["price"],
                "shares" => $asset["shares"],
            ];
            log_action($action);

            user_delete_asset($_SESSION["id"], $stock["symbol"]);
            user_update_cash($_SESSION["id"], $cash);
            $positions = user_get_positions($_SESSION["id"]);

            // render portfolio
            render("sell_form.php", ["title" => "Portfolio", "positions" => $positions]);
        }
        else
        {
            apologize("You do not have that asset in your portfolio.");
        }

    }


?>
