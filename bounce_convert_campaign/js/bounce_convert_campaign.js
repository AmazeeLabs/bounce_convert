jQuery(document).ready(function() {
    jQuery("body").mouseleave(function() {
        var visited = jQuery.cookie('bounce_convert_cookie');
        if (visited === 'yes') {
            return false;
        } else {
            //@cookie_expiry set value while create bounce convert campaign
            var cookie_expiry = Drupal.settings.bounce_convert_campaign.cookie_expiry;
            //to click the hidden link of modal form
            jQuery(".ctools-use-modal-processed").trigger("click");
        }
        //setting cookie expiry time by (s * ms)
        var date = new Date();
        date.setTime(date.getTime() + (cookie_expiry * 1000));
        jQuery.cookie('bounce_convert_cookie', 'yes', {expires: date});
    });
}); 