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
    
	if (empty($_POST["password"]) || empty($_POST["confirmation"]))
	{
		apologize("password left blank.");
	}

	if (empty($_POST["username"]))
	{
		apologize("usename not in database");
	}

	if ($_POST["password"] != $_POST["confirmation"])
	{
		apologize("passwords do not match.");
	}
	
	else
	{
		$result = query("INSERT INTO users (username, hash, cash, email) VALUES (?, ?, 10000.00, ?)", $_POST["username"], crypt($_POST["password"]), $_POST["email"]);
		if ($result === false)
		{
			apologize("An error occured with your username. Username may already exist.");
		}
		$rows = query("SELECT LAST_INSERT_ID() AS id");
		$id = $rows[0]["id"];
		$_SESSION["id"] = $id;
		
		// redirect to portfolio
        redirect("/");
	}		
    }

?>
