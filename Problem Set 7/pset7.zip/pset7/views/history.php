<div>
    <table class='table table-striped table-responsive'>
        <thead>
            <tr>
                <th>Transaction</th>
                <th>Date/Time</th>
                <th>Symbol</th>
                <th>Shares</th>
                <th>Price (USD)</th>
            </tr>
        </thead>
        <tbody>
            <?php foreach ($history as $row): ?>
            <tr>
                <td><?= $row["transaction"] ?></td>
                <td><?= $row["datetime"] ?></td>
                <td><?= $row["symbol"] ?></td>
                <td><?= $row["shares"] ?></td>
                <td><?= $row["price"] ?></td>
            </tr>
            <?php endforeach ?>
        </tbody>
    </table>
</div>
