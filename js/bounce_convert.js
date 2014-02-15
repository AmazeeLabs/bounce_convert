//jQuery(document).ready(function() {
//    jQuery("body").mouseleave(function() {
//        var visited = jQuery.cookie('bounce_convert_cookie');
//        if (visited === '1') {
//          return false;
//        } else {
//            //@cookie_expiry set value while create bounce convert campaign
//            var cookie_expiry = Drupal.settings.bounce_convert.cookie_expiry;
//            //to click the hidden link of modal form
//            jQuery(".ctools-use-modal-processed").trigger("click");
//        }
//        //setting cookie expiry time by (s * ms)
//        var date = new Date();
//        date.setTime(date.getTime() + (cookie_expiry * 1000));
//        jQuery.cookie('bounce_convert_cookie', '1', {expires: date});
//    });
//}); 


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
                    if (visited === '1') {
                        return false;
                    } else {
                        //@cookie_expiry set value while create bounce convert campaign
                        var cookie_expiry = Drupal.settings.bounce_convert.cookie_expiry;
                        //@webform_id webform id related to campaign
                        var webform_id = Drupal.settings.bounce_convert.webform_id;
                        //to click the hidden link of modal form
                        jQuery(".ctools-use-modal-processed").trigger("click");
                        // Ajax call to register impression
                        jQuery.ajax({
                            type: 'POST',
                            url: Drupal.settings.basePath + "bounce_convert_impression",
                            data: {
                                wid: webform_id,
                            },
                            success: function(data) {
//                                alert(data);
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
function bounce_convert_jumpto(url) {

    if (document.form1.jumpmenu.value != "null") {
        document.location.href = url;
    }
}