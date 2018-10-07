<?php
include_once('conn.php');

$firstname=$_POST["firstname"];
$lastname=$_POST["lastname"];
$email=$_POST["email"];
$mobile=$_POST["mobile"];
$designation=$_POST["designation"];

if($firstname=='' || $lastname=='' || $email=='' || $mobile=='' || $designation=='' )
{
    echo "Please fill all fields";
}
else
{
 $query="insert form_data(first_name,last_name,email,mobile,designation) values('$firstname','$lastname','$email','$mobile','$designation')";
//echo $query;


 $result=mysqli_query($link,$query);
 if(mysqli_affected_rows($link)==1)
 {
     echo"data inserted successfully";
 }
 else 
 {
     echo "not inserted";
 }
}


?>