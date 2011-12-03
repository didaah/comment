/* $Id$ */

$(function() {
	
  $('.comment_quote').click(function() {
    var cid = $(this).attr('alt');
    if (cid) {
    	var root = $(this).closest('.comment_view');
    	if (root) {
	      var q = root.find('.comment_body').eq(0).text();
	      if (q) {
	        var n = root.find('.comment_name').eq(0).text() + '说：';
	        n = n.replace(/\s/ig, '');
	        q = n + q + "\n------------------------------------------\n";
	        var v = $('#comment_form_type_body').val();
	        $('#comment_form_type_body').val(v + q);
	      }
    	}
    }
  });
  
  $('.comment_reply').click(function() {
    var cid = $(this).attr('alt');
    if (cid) {
    	var root = $(this).closest('.comment_view');
    	
    	if (root) {
	    	var n = root.find('.comment_name').eq(0).text();
	      n = '[comment@' + n.replace(/\s/ig, '')+'='+cid+']';
	      $('#comment_form_type_body').val($('#comment_form_type_body').val() + n);
    	}
    }
  });
  
  if (settings.comment_anonymous_name) {
	  var anonymous = Dida.getck('comment_anonymous');
	  if (anonymous) {
	  	if (anonymous.indexOf('[#@#]') != -1) {
	  		var a = anonymous.split('[#@#]');
	  		if (a[0]) $('#comment_form_type_name').val(a[0]);
	  		if (a[1]) $('#comment_form_type_mail').val(a[1]);
	  		if (a[2]) $('#comment_form_type_site').val(a[2]);
	  	}
	  } else {
	  	$('#comment_form_type_name').val(settings.comment_anonymous_name);
	  }
  }
  
});