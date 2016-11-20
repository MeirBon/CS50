<div>
    <table id = "table">
        <tr>
            <th>Symbol</th>
            <th>Name</th>
            <th>Shares</th>
            <th>Price</th>
            <th>Total</th>
        </tr>
        <?php
            // get user portfolio
            $positions = CS50::query("SELECT * FROM portfolios WHERE user_id = ?", $_SESSION["id"]);
            $userinfo = CS50::query("SELECT cash FROM users WHERE id = ?", $_SESSION["id"]);
            
            // get user's cash
            $cash = number_format($userinfo[0]["cash"], 4);
            
            // go over each entry
            foreach ($positions as $position)
            {
                // get stock price
                $stock = lookup($position["symbol"]);
                $position["total"] = number_format(($stock["price"] * $position["shares"]), 4);
                
                // print user's shares
                print("<tr>");
                print("<td>" . $position["symbol"] . "</td>");
                print("<td>" . $stock["name"] . "</td>");
                print("<td>" . $position["shares"] . "</td>");
                print("<td>$" . number_format($stock["price"], 4) . "</td>");
                print("<td>$" . $position["total"] . "</td>");
                print("</tr>");
            }
            
            // print user's cash
            print("<tr>");
            print("<td>" . 'Cash' . "</td>");
            print("<td>" . ' ' . "</td>");
            print("<td>" . ' ' . "</td>");
            print("<td>" . ' ' . "</td>");
            print("<td>$" . $cash . "</td>");
            print("</tr>");
    
        ?>
    </table>
</div>
