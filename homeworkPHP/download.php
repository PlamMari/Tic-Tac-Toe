<?php

$file = "./uploads/".($_GET["f"]);
if(is_file($file)){
    header("Content-type:application/bin-hex");
    header("Content-disposition:attachment; filename=".basename($file));
    readfile($file);
} else {
    echo "<h1>ERROR</h1>";
}