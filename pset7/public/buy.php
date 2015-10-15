<?php

    // configuration
    require("../includes/config.php"); 

    
    // validate submission
    // if user reached page via GET (as by clicking a link or via redirect)
    if ($_SERVER["REQUEST_METHOD"] == "GET")
    {
        $cash = query("SELECT cash, username FROM users WHERE id = ?", $_SESSION["id"]);
        // else render form
        render("buy_form.php", ["title" => "Buy", "cash" => $cash]);
    }

    // else if user reached page via POST (as by submitting a form via POST)
    else if ($_SERVER["REQUEST_METHOD"] == "POST")
    {
        if (empty($_POST["symbol"]))
        {
            apologize("You must provide a stock symbol.");
        }
        if (empty($_POST["shares"]))
        {
            apologize("You must provide an amount of shares to buy.");
        }
        else
        {
            $stock = lookup($_POST["symbol"]);
            if ($stock === false)
            {
                apologize("Invalid stock symbol.");
            }
            
            if ( preg_match("/^\d+$/", $_POST["shares"]) == 1)
            {
                // calculate total sale value (stock's price * shares)
                $value = $stock["price"] * $_POST["shares"];
                
                $cash = query("SELECT cash FROM users WHERE id = ?", $_SESSION["id"]);
                $stock["symbol"] = strtoupper ($stock["symbol"]);
                
                if ($cash > $value)
                {
                    // insert the stock from their portfolio 
                    query("INSERT INTO Portfolio (id, symbol, shares) VALUES(?, ?, ?) ON DUPLICATE KEY UPDATE shares = shares + VALUES(shares)", $_SESSION["id"], $stock["symbol"], $_POST["shares"]); 
                    if ($query === false)
                    {
                        apologize("Error while inserting shares.");
                    }
                    
                    // subtract the sale value from cash
                    query("UPDATE users SET cash = cash - ? WHERE id = ?", $value, $_SESSION["id"]);
                    
                    if ($query === false)
                    {
                        apologize("Error while updating cash.");
                    }
                    
                    //update history
                    query("INSERT INTO history (action, id, symbol, shares, price, date) VALUES('BOUGHT', ?, ?, ?, ?, ?)", $_SESSION["id"], $stock["symbol"], $_POST["shares"], $stock["price"], date("Y-m-d H:i:s"));
                    
                    redirect("/");
                }
                else
                {
                    apologize("You do not have enough money to purchase shares.");
                }
            }
            else
            {
                apologize("Please provide a valid amount.");
            }
        }
    }
        
?>
