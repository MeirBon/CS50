<form action="sell.php" method="post">
    <fieldset>
        <p>
            Enter the amount you want to sell.
        </p>
        <div class="form-group">
            <input class="form-control" name="shares" placeholder="Amount or 'all'" type="text"/>
        </div>
        <div class="form-group">
            <select class="form-control" name="symbol">
                <option disabled selected value="">Symbol</option>
                <?php
                // create options
                foreach ($options as $symbol)
                {
                    // create option
                    print("<option value='".$symbol["symbol"]."'>".$symbol["symbol"]."</option>");
                }
                ?>
            </select>
        </div>
        <div class="form-group">
            <button class="btn btn-default" type="submit">
            Sell
            </button>
        </div>
    </fieldset>
</form>