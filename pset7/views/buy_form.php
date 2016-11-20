<form action="buy.php" method="post">
    <fieldset>
        <div class="form-group">
            <input autocomplete="off" autofocus class="form-control" name="symbol" placeholder="Symbol" type="text"/>
        </div>
        <div class="form-group">
            <input class="form-control" name="shares" placeholder="Shares" type="number" min="0"/>
        </div>
        <div class="form-group">
            <button class="btn btn-default" type="submit">
                <span aria-hidden="true"></span>
                Buy
            </button>
        </div>
        <p>
            Want to add money to your account?
            <a href="add.php">Click here.</a>
        </p>
    </fieldset>
</form>
