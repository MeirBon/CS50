<div>
    <table id = "table">
        <tr>
            <th>Transaction ID</th>
            <th>Name</th>
            <th>Symbol</th>
            <th>Shares</th>
            <th>Type</th>
            <th>Price</th>
        </tr>
        <?php
            // get user portfolio
            $history = CS50::query("SELECT * FROM history WHERE user_id = ?", $_SESSION["id"]);
            
            foreach ($history as $transaction)
            {
                $name = lookup($transaction["symbol"]);
                
                print("<tr>");
                print("<td>" . $transaction["id"] . "</td>");
                print("<td>" . $name["name"] . "</td>");
                print("<td>" . $transaction["symbol"] . "</td>");
                print("<td>" . $transaction["shares"] . "</td>");
                print("<td>" . $transaction["transaction"] . "</td>");
                print("<td>$" . number_format($transaction["price"], 4) . "</td>");
                print("</tr>");
            }
            
            if ($history == NULL)
            {
                print("You have no transactions in your history.");
            }
        ?>
    </table>
        <form action="history.php" method="post">
            <div class="form-group">
                <button class="btn btn-default" type="submit" id="clear">
                    <span aria-hidden="true"></span>
                    Clear History
                </button>
            </div>
        </form>
</div>