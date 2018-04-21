/**
 * Created by peiren on 21.06.17.
 */

<!-- Table js from Datatables' template -->
$(document).ready(function() {
    $('#first_page').dataTable();
} );

$(function(){
    $('#indexMenu li').click(function(){
        var current = $(this),
        target = current.find('a').attr('target');
        $.get(target,function(data){
            $("#frameContent").html(data);
         });
    });
});
<!-- Table js from Datatables' template -->
function ajax_test() {
    $.ajax( {
        type : "POST",
        url : "/",
        dataType : "json",
        data : "",
        error: function(XMLResponse) {
            alert(XMLResponse.responseText )
        },
        success : function(data) {
            $( "#hh1" ).text(data);
        }
    } );
    return false;
};

function load_content() {
    $.ajax( {
        type : "POST",
        url : "/table",
        dataType : "json",
        data : "",
        error: function(XMLResponse) {
            alert(XMLResponse.responseText )
        },
        success : function(data) {
            $( "#frameContent" ).text(data);
        }
    } );
    return false;
};

<!-- Table js from Datatables' template
$(function(){
    $.get("index.html",function(data){
        $("#frameContent").html(data);
    });

    $('#indexMenu li').click(function(){
        var current = $(this),
        target = current.find('a').attr('target');
        $.get(target,function(data){
            $("#frameContent").text(data);
         });
    });
});-->