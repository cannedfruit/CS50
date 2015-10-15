<form action="sell.php" method="post">
<fieldset>
    <div class="form-group">
        <input autofocus class="form-control" name="symbol" placeholder="symbol" type="text"/>
    </div>
    <br><br>
    <input type="submit" value="Submit">
</fieldset>
</form>
<br>
</br>
<div>
    <h4>
        User: <?= $cash[0]["username"]?>
    </h4>
    <h4>
        Total cash: $<?= $cash[0]["cash"]?>
    </h4>
</div>
<br>
</br>
<div>
    <p>
        <a href="quote.php">Search for a stock price</a>
    </p>
    <p>
        <a href="buy.php">Buy stock</a>
    </p>
    <p>
        <a href="index.php">Return to your portfolio</a>
     </p>
    <p>
        <a href="logout.php">Log Out</a>
    </p>
</div>
