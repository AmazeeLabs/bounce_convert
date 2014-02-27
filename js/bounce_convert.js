/**
 * @file
 * Handle Bounce Conver modal and cookie for users
 */
(function() {

    var current_scroll = 0;
    var last_mouse_y = null;
    jQuery(document)
            .scroll(function() {
                current_scroll = jQuery(this).scrollTop();
            })
            .mousemove(function(e) {
                var speed = last_mouse_y - e.pageY;
                var success_val = e.pageY - speed;
                if (success_val < last_mouse_y && success_val <= current_scroll) {
                    var visited = jQuery.cookie('bounce_convert_cookie');
                    // If cookie time is not expired or Modal/Popup is alreay open
                    if (visited === '1' || jQuery(".popups-container").length > 0) {
                        return false;
                    } else {
                        //@cookie_expiry set value while create bounce convert campaign
                        var cookie_expiry = Drupal.settings.bounce_convert.cookie_expiry;
                        //@webform_id webform id related to campaign
                        var webform_id = Drupal.settings.bounce_convert.webform_id;
                        //@page_path current page path
                        var page_path = Drupal.settings.bounce_convert.page_path;
                        //@campaign_id Campaign ID
                        var campaign_id = Drupal.settings.bounce_convert.campaign_id;
                        //to click the hidden link of modal form
//                        jQuery(".ctools-use-modal-processed").trigger("click");
//                        alert("sdf");
                        jQuery("#modalContent").css("display", "block");
                        jQuery("#modalBackdrop").css("display", "block");
                        jQuery("#modalContent").show();
                        jQuery("#modalBackdrop").show();
                        // Ajax call to register impression
                        jQuery.ajax({
                            type: 'POST',
                            url: Drupal.settings.basePath + "bounce_convert_impression",
                            data: {
                                webform_id: webform_id,
                                page_path: page_path,
                                campaign_id: campaign_id
                            },
                            success: function(data) {
                                //data saved to DB
                            }
                        });
                    }
                    //setting cookie expiry time by (s * ms)
                    var date = new Date();
                    date.setTime(date.getTime() + (cookie_expiry * 1000));
                    jQuery.cookie('bounce_convert_cookie', '1', {expires: date});
                }

                last_mouse_y = e.pageY;
            });
})();

jQuery(function() {
    jQuery(".ctools-use-modal-processed").trigger("click");

    jQuery(".bounce-convert-filter-options").hover(
            function() {
                jQuery(".bounce-convert-filter-options ul").show(500);
            }, function() {
        jQuery(".bounce-convert-filter-options ul").hide(500);
    });
});
