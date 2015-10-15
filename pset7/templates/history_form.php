<div>
    <table border="3" style="width:100%">
        <?php foreach ($positions as $position): ?>
                <tr>
                    <th>Action</th>
                    <th>Symbol</th>
                    <th>Shares</th>
                    <th>Price</th>
                    <th>Value</th>
                    <th>Date</th>
                </tr>
                </tr>
                </tr>
                <tr><td><?= $position["action"] ?></td>
                    <td><?= $position["symbol"] ?></td>
                    <td><?= $position["shares"] ?></td>
                    <td><?= $position["price"] ?></td>
                    <td><?= $position["price"] * $position["shares"]?></td>
                    <td><?= $position["date"] ?></td>
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
        <a href="index.php">Return to Portfolio</a>
    </p>
    <p>
        <a href="logout.php">Log Out</a>
    </p>
</div>
