<h2> Positions </h2>
<form action="sell.php" method="post">
    <table class='table table-striped table-responsive'>
        <thead>
            <tr>
                <th>Symbol</th>
                <th>Shares</th>
                <th>Price (USD)</th>
                <th>Sell</th>
            </tr>
        </thead>
        <tbody>
            <?php foreach ($positions as $position): ?>
            <tr>
                <td><?= $position["symbol"] ?></td>
                <td><?= $position["shares"] ?></td>
                <td><?= $position["price"] ?></td>
                <td>
                    <button class="btn btn-default" type="submit" name="sell-symbol" value="<?= $position["symbol"] ?>">
                        <span aria-hidden="true" class="glyphicon glyphicon-arrow-right"></span>
                    </button>
                </td>
            </tr>
            <?php endforeach ?>
        </tbody>
    </table>
</form>
