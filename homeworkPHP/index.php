<?php
    function dir_exists($filename)
    {
        return file_exists($filename) && is_dir($filename);
    }

    $galleries = ['Animals', 'Buildings', 'Cars', 'Plants', 'Water', 'Sky', 'People'];
    sort($galleries);
    $uploadStatus= [
        "messages" => Array(),
        "success" => false
    ];

    /*echo "<pre>";
    var_dump($_FILES);
    var_dump($_POST);
    var_dump($_GET);
    echo "</pre>";*/

    $allowedext = ['jpg', 'jpeg', 'png', 'gif', 'bmp'];

    $fileUploadOk= isset($_FILES['userfile']) && $_FILES['userfile']['error']=== 0;
    $postDataOk= isset($_POST["gallery"]);
    
    if($postDataOk && $fileUploadOk) {

        $userfileArr= $_FILES['userfile'];

        $uploadedFileInfo = pathinfo($userfileArr['name']);

        $uploadedFileExt= strtolower($uploadedFileInfo['extension']);
        $uploadedFileBaseName= strtolower($uploadedFileInfo['basename']);

        $gallery= $_POST["gallery"];
        $fileExtIsValid= in_array($uploadedFileExt, $allowedext)!== false;
        $galleryNameIsValid= in_array($gallery, $galleries)!== false;

        if(!$fileExtIsValid){
            $uploadStatus["success"]= false;
            array_push($uploadStatus["messages"], "File \"$uploadedFileBaseName\" has an extension which is not allowed.");
        }
        if(!$galleryNameIsValid){
            $uploadStatus["success"]= false;
            array_push($uploadStatus["messages"], "Gallery \"$uploadedFileBaseName\" has an extension which is not allowed.");
        }

        if($fileExtIsValid && $galleryNameIsValid) {
            $uploadFolder= "./uploads/$gallery/";
            $tmpFileName= $userfileArr["tmp_name"];
            if(!dir_exists($uploadFolder)){
                mkdir($uploadFolder, 666);
            }
            move_uploaded_file($tmpFileName, $uploadFolder.$uploadedFileBaseName);
            $uploadStatus["success"]= true;
            array_push($uploadStatus["messages"], "File \"$uploadedFileBaseName\" uploaded to gallery \"$gallery\" successfully.");
        }
    }

    
function imageCreateFromAny($filepath) {
    $type = exif_imagetype($filepath);
    $allowedTypes = array(
        1,  // [] gif
        2,  // [] jpg
        3,  // [] png
        6   // [] bmp
    );
    if (!in_array($type, $allowedTypes)) {
        return false;
    }
    switch ($type) {
        case 1 :
            $img = imagecreatefromgif($filepath);
        break;
        case 2 :
            $img = imagecreatefromjpeg($filepath);
        break;
        case 3 :
            $img = imagecreatefrompng($filepath);
        break;
        case 6 :
            $img = imagecreatefrombmp($filepath);
        break;
    }   
    return $img; 
}
?>

<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <meta http-equiv="X-UA-Compatible" content="IE=edge">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <!-- Bootstrap CSS -->
    <link rel="stylesheet" href="./css/bootstrap.min.css"/>

    <link rel="stylesheet" href="./css/styles.css"/>
    <title>Document</title>
</head>
<body>

<div id="page-container" class="row-fluid">
    <div class="page-row nav"><h1>Galleries</h1></div>
    <div class="col-xs-12">
        <!--
        <form method="POST">
            <input name="username" type="text" value=""/>
            <input name="password" type="password" value=""/>
            <input name="secret" type="hidden" value="Silistra22"/>
            <input type="submit" value="Submit" />
        </form>
        -->
        <div class="page-row">
            <h2>Upload a new image</h2>
            <form enctype="multipart/form-data" method="POST" class="form-inline upload-form">
            <div class="form-group">
                <label for="gallery">Choose gallery</label>
                <select class="form-control" name="gallery">
                <?php 
                foreach($galleries as $gallery) {
                    echo "<option value=\"$gallery\">$gallery</option>";
                }
                ?>
                </select>
            </div>
            <div class="form-group">
                <label for="userfile">Send this file</label>
                <input name="userfile" class="form-control" type="file"/>
            </div>
            <input class="btn btn-default" type="submit" value="Send File" />
            </form>
        <?php
            $messClass= $uploadStatus["success"]=== true? "bg-success": "bg-danger";
            foreach($uploadStatus["messages"] as $message) {
                echo "<div class='hideMe $messClass'>$message</div>";
            }
        ?>
        </div>

        <div class="page-row">
        <?php
            foreach($galleries as $gallery){
                $galleryDirName= "./uploads/$gallery/";       
                if(dir_exists($galleryDirName)) {
                    echo "<h2>$gallery</h2>";
                    echo "<div class=\"row\">";

                    $galleryDir = dir($galleryDirName);
                    while (($fileInGalleryDir = $galleryDir->read()) !== false) {

                        if($fileInGalleryDir === ".") continue;
                        if($fileInGalleryDir === "..") continue;
                        if($fileInGalleryDir === "thumbs") continue;
                        $size = filesize($galleryDirName.$fileInGalleryDir);
                        $fsize = $size;
                        if ($size>1024) $fsize = round($size/1024)." Kb";
                        echo "<div class=\"column image-box\">";

                        echo "$fsize <a href='download.php?f=$gallery/$fileInGalleryDir' target=_>$fileInGalleryDir</a><br>";
                        echo "<img class=\"img-thumbnail\" src=\"getthumb.php?file=$galleryDirName$fileInGalleryDir\"><br/>"; // width=\"200\"
                        echo "</div>";
                    }
                    echo "</div>";
                }
            }
        ?>
        </div>

    </div>
</div>

</body>
</html>