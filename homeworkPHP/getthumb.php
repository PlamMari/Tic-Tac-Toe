<?php

function dir_exists($filename)
{
    return file_exists($filename) && is_dir($filename);
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

$badfilename= "";//"imagenotfound.png"

$imagefilename= isset($_GET['file']) ? $_GET['file']: $badfilename;
if (file_exists($imagefilename)) {
    $filePathInfo = pathinfo($imagefilename);
    //var_dump($filePathInfo);
    $thumbdir= $filePathInfo["dirname"]."/thumbs/";
    if(!dir_exists($thumbdir)){
        mkdir($thumbdir, 666);
    }
    $thumbimagefilename = $thumbdir.$filePathInfo["filename"].".png";

    if (!file_exists($thumbimagefilename)){
        $maxThumbWidth = 240;
        $maxThumbHeight = 240;
        $info = getimagesize($imagefilename);
        $k = max($info[0]/$maxThumbWidth, $info[1]/$maxThumbHeight);
        $thumbWidth = round($info[0]/$k);
        $thumbHeight = round($info[1]/$k);
        $start_x = (int) ($maxThumbWidth - $thumbWidth)/2;
        $start_y = (int) ($maxThumbHeight - $thumbHeight)/2;
        $imgToResize = imageCreateFromAny($imagefilename);
        $thumbnail = imagecreatetruecolor($maxThumbWidth, $maxThumbHeight);

        $bgcolor = imagecolorallocate($thumbnail, 90,60,90);
        imagecolortransparent($thumbnail, $bgcolor);
        imagefill($thumbnail, 0,0, $bgcolor);

        imagecopyresampled($thumbnail, $imgToResize, $start_x, $start_y, 0, 0, $thumbWidth, $thumbHeight, $info[0], $info[1]);

        imagepng($thumbnail, $thumbimagefilename);
        imagedestroy($imgToResize);
        imagedestroy($thumbnail);
    }
    $imagefilename= $thumbimagefilename;
}
else {
    $imagefilename = $badfilename;
}

header('Content-type: image/png');

$image = imageCreateFromAny($imagefilename);
imagepng($image);
imagedestroy($image);
?>
