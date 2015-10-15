<?php

    // configuration
    require("../includes/config.php");
    
    $rows = query("SELECT * FROM history WHERE id = ?", $_SESSION["id"]);
    $positions = [];
    
    foreach ($rows as $row)
    {
        $stock = lookup($row["symbol"]);
        if ($stock !== false)
        {
            $positions[] = [
                "action" => $row["action"],
                "symbol" => $row["symbol"],
                "shares" => $row["shares"],
                "price" => $stock["price"],
                "date" => $row["date"],
            ];
        }
    }
    
    $cash = query("SELECT cash, username FROM users WHERE id = ?", $_SESSION["id"]);
    
    // render portfolio
    render("history_form.php", ["title" => "Portfolio", "positions" => $positions, "cash" => $cash]);
    

?>
