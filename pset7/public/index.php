<?php

    // configuration
    require("../includes/config.php");
    
    $id = $_SESSION["id"];
    $rows = query("SELECT symbol, shares, id FROM Portfolio WHERE id = $id");
    $positions = [];
    
    foreach ($rows as $row)
    {
        $stock = lookup($row["symbol"]);
        if ($stock !== false)
        {
            $positions[] = [
                "name" => $stock["name"],
                "price" => $stock["price"],
                "shares" => $row["shares"],
                "symbol" => $row["symbol"]
            ];
        }
    }
    
    $cash = query("SELECT cash, username FROM users WHERE id = $id");
    
    // render portfolio
    render("portfolio.php", ["title" => "Portfolio", "positions" => $positions, "cash" => $cash]);
    

?>
