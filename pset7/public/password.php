<?php

    // configuration
    require("../includes/config.php");
    // require PHPMailer
    require_once("libphp-phpmailer/class.phpmailer.php"); 

    // if user reached page via GET (as by clicking a link or via redirect)
    if ($_SERVER["REQUEST_METHOD"] == "GET")
    {
        // else render form
        render("password_form.php", ["title" => "Password"]);
    }

    // else if user reached page via POST (as by submitting a form via POST)
    else if ($_SERVER["REQUEST_METHOD"] == "POST")
    {
        // validate submission
        if (empty($_POST["email"]))
        {
            apologize("You must provide your email.");
        }

        // query database for user
        $rows = query("SELECT * FROM users WHERE email = ?", $_POST["email"]);

        // if we found user, check password
        if (count($rows) == 1)
        {
            // first (and only) row
            $row = $rows[0];

            // compare email of user's input against email that's in database
            if ($_POST["email"] == $row["email"])
            {
            
                //generate a new random password
                $length = 8;
                $chars = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789!@#$%^&*()_-=+;:,.?";
                $password = substr( str_shuffle( $chars ), 0, $length );
                if($password === false)
                {
                    apologize("Error generating password.");
                }
                else
                {
                    //
                    query("UPDATE users SET hash = ? WHERE email = ? ", crypt($password), $_POST["email"]); 
                    
                    
                    // instantiate mailer
                    $mail = new PHPMailer();

                    // use SMTP
                    $mail->IsSMTP();
                    $mail->Host = "smtp.gmail.com";

                    $mail->SMTPAuth = true;                          
                    //Provide username and password     
                    $mail->Username = "cs50onetime@gmail.com";                 
                    $mail->Password = "cs50password";                           
                    //If SMTP requires TLS encryption then set it
                    $mail->SMTPSecure = "tls";                           
                    //Set TCP port to connect to 
                    $mail->Port = 587;                                   
                    
                    //set from
                    $mail->From = "cs50onetime@gmail.com";

                    // set To:
                    $mail->AddAddress($row["email"]);
                    

                    $mail->Subject = "Subject Text";
                    $mail->Body = "Please login to your account using your new password: " . $password;
                    

                    // send text
                    if ($mail->Send())
                    {
                        redirect("../login.php");
                    }
                    else
                    {
                        // redirect to confirmation
                    redirect("../templates/pass_conf.php");
                    }
                }
            }
        }

        // else apologize
        apologize("Invalid email.");
    }

?>
