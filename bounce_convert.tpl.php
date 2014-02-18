<form name="form1">
  <select name="jumpmenu" onChange="bounce_convert_jumpto(document.form1.jumpmenu.options[document.form1.jumpmenu.options.selectedIndex].value)">
    <option>Select</option>
    <option value="http://localhost/drupal7/bounce-convert/1/results<?php print $bounce_convert_filter_url; ?>/today">Today</option>
    <option value="http://localhost/drupal7/bounce-convert/1/results<?php print $bounce_convert_filter_url; ?>/yesterday">Yesterday</option>
    <option value="http://localhost/drupal7/bounce-convert/1/results<?php print $bounce_convert_filter_url; ?>/7days">Last 7 Days</option>
    <option value="http://localhost/drupal7/bounce-convert/1/results<?php print $bounce_convert_filter_url; ?>/30days">Last 30 Days</option>
    <option value="http://localhost/drupal7/bounce-convert/1/results<?php print $bounce_convert_filter_url; ?>/this-month">This Month</option>
    <option value="http://localhost/drupal7/bounce-convert/1/results<?php print $bounce_convert_filter_url; ?>/last-month">Last Month</option>
  </select>
</form>
<?php if ($bounce_convert_filter_url == '/percentage') { ?>
  <div style="font-size:150px;"><?php print $bounce_convert_percentage ?> %</div>
  <?php
}