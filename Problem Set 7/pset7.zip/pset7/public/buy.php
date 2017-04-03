<?php

    // configuration
    require("../includes/config.php");

    // if user reached page via GET (as by clicking a link or via redirect)
    if ($_SERVER["REQUEST_METHOD"] == "GET")
    {
        // else render form
        render("buy_form.php", ["title" => "Buy"]);
    }

    // else if user reached page via POST (as by submitting a form via POST)
    else if ($_SERVER["REQUEST_METHOD"] == "POST")
    {
        if ($_POST["symbol"] == "" || $_POST["shares"] == "")
        {
            apologize("Both the stock symbol and the number of shares are required.");
        }
        if (!preg_match("/^\d+$/", $_POST["shares"]))
        {
            apologize("The number of shares value needs to be a non negative integer.");
        }

        $stock = lookup($_POST["symbol"]);
        if (!$stock)
        {
            apologize("Stock does not exist.");
        }
        
        $cost = $_POST["shares"] * $stock["price"];
        $cash = user_get_cash($_SESSION["id"]);

        if ($cost > $cash)
        {
            apologize("You cannot afford this stock.");
        }

        user_update_cash($_SESSION["id"], -$cost);
        user_update_portfolio($_SESSION["id"], $stock["symbol"], $_POST["shares"]);
        $action = [
            "transaction_type" => "BUY",
            "user_id" => $_SESSION["id"],
            "symbol" => $stock["symbol"],
            "price" => $stock["price"],
            "shares" => $_POST["shares"],
        ];
        log_action($action);

        render("buy.php", [
            "title" => "Bought",
            "symbol" => htmlspecialchars($stock["symbol"]),
            "name" => htmlspecialchars($stock["name"]),
            "price" => number_format($stock["price"], 4),
            "shares" => $_POST["shares"],
            "cost" => number_format($cost),
        ]);

    }

?>
