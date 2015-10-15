<div>
    <table border="3" style="width:100%">
        <?php foreach ($positions as $position): ?>
                <tr>
                    <th>Symbol</th>
                    <th>Shares</th> 
                    <th>Price</th>
                    <th>Total Value</th>
                </tr>
                <tr>
                    <td><?= $position["symbol"] ?></td>
                    <td><?= $position["shares"] ?></td>
                    <td><?= $position["price"] ?></td>
                    <td><?= $position["price"] * $position["shares"]?></td>
                </tr>

        <?php endforeach ?>
    </table>
</div>
<div>
    <h4>
        User: <?= $cash[0]["username"]?>
    </h4>
    <h4>
        Total cash: $<?= $cash[0]["cash"]?>
    </h4>
</div>
<div>
    <p>
        <a href="buy.php">Buy stock</a>
    </p>
    <p>
        <a href="sell.php">Sell stock</a>
    </p>
    <p>
        <a href="quote.php">Search for a stock price</a>
    </p>
    <p>
        <a href="history.php">History</a>
    </p>
    <p>
        <a href="change.php">Change Password</a>
    </p>
    <p>
        <a href="logout.php">Log Out</a>
    </p>
</div>
