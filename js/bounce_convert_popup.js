/**
 * @file
 * Provide the HTML to create the modal dialog.
 */
Drupal.theme.prototype.BounceConertPopup = function() {
    var html = '';

    html += '<div id="ctools-modal" class="popups-box">';
    html += '  <div class="ctools-modal-content modal-forms-modal-content">';
    html += '    <div class="popups-container bounce-convert-custom-modal">';
    html += '      <div class="modal-header popups-title">';
    html += '        <span class="popups-close close">' + Drupal.CTools.Modal.currentSettings.closeText + '</span>';
    html += '        <div class="clear-block"></div>';
    html += '      </div>';
    html += '      <div class="modal-scroll"><div id="modal-content" class="modal-content popups-body"></div></div>';
    html += '    </div>';
    html += '  </div>';
    html += '</div>';

    return html;
};