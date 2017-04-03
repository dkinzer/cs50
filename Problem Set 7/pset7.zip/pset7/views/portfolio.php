<h2> Cash: $<?= $cash ?></h2>

<h2> Positions </h2>
<div>
    <table class='table table-striped table-responsive'>
        <thead>
            <tr>
                <th>Symbol</th>
                <th>Shares</th>
                <th>Price (USD)</th>
            </tr>
        </thead>
        <tbody>
            <?php foreach ($positions as $position): ?>
            <tr>
                <td><?= $position["symbol"] ?></td>
                <td><?= $position["shares"] ?></td>
                <td><?= $position["price"] ?></td>
            </tr>
            <?php endforeach ?>
        </tbody>
    </table>
</div>
