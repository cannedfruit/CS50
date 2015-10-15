<?php

    // configuration
    require("../includes/config.php"); 

    
    // validate submission
    // if user reached page via GET (as by clicking a link or via redirect)
    if ($_SERVER["REQUEST_METHOD"] == "GET")
    {
        $cash = query("SELECT cash, username FROM users WHERE id = ?", $_SESSION["id"]);
        // else render form
        render("sell_form.php", ["title" => "Sell", "cash" => $cash]);
    }

    // else if user reached page via POST (as by submitting a form via POST)
    else if ($_SERVER["REQUEST_METHOD"] == "POST")
    {
        if (empty($_POST["symbol"]))
        {
            apologize("You must provide a stock symbol.");
        }
        else
        {
            $stock = lookup($_POST["symbol"]);
            $stock["symbol"] = strtoupper ($stock["symbol"]);
            if ($stock === false)
            {
                apologize("Invalid stock symbol.");
            }
            $shares = query("SELECT shares FROM Portfolio WHERE id = ? AND symbol = ?", $_SESSION["id"], $_POST["symbol"]);
            
            if (count($shares) == 1)
            {
                // calculate total sale value (stock's price * shares)
                $value = $stock["price"] * $shares[0]["shares"];
                
                // delete the stock from their portfolio 
                query("DELETE FROM Portfolio WHERE id = ? AND symbol = ?", $_SESSION["id"], $_POST["symbol"]); 
                
                // add the sale value to cash
                query("UPDATE users SET cash = cash + $value WHERE id = ?", $_SESSION["id"]);
                
                //update history
                query("INSERT INTO history (action, id, symbol, shares, price, date) VALUES('SOLD', ?, ?, ?, ?, ?)", $_SESSION["id"], $stock["symbol"], $shares[0]["shares"], $stock["price"], date("Y-m-d H:i:s"));
                    
                redirect("/");
            }
            else
            {
                apologize("You do not own this stock.");
            }
        }
    }
        
?>
