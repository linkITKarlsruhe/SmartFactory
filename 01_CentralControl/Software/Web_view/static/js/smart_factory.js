/**
 * Created by Peiren Yang on 21.06.17.
 */

<!-- Table js from Datatables' template -->
$(document).ready(function() {
    $('#first_page').dataTable();
} );

function load_content(re_page) {
$.ajax( {
    type : "POST",
    url : re_page,
    dataType : "json",
    data : "",
    error: function(XMLResponse) {
        //alert(XMLResponse.responseText
        $('#frameContent').html(XMLResponse.responseText)
    },
    success : function(data) {
        $('#frameContent').html(data);
        $('#first_page').dataTable();
    }
});
return false;
};
$(document).ready(function() {
  $('li').click( function() {
      $('.active').removeClass('active')
      $(this).addClass('active')
      load_content($(this).find('a').text())
  })
});