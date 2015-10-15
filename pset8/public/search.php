<?php

    require(__DIR__ . "/../includes/config.php");

    // numerically indexed array of places
    $places = [];
    $query = preg_split("/[\s,]+/", htmlspecialchars($_GET['geo']));
    
    // remove "US" from query
    if (($index = array_search("US", $query)) !== false) {
        unset($query[$index]);
    }   
    
    $sql = 'SELECT * FROM `places` USE INDEX(`location`) WHERE ';

    // TODO: search database for places matching $_GET["geo"]
    for ($i = 0, $count = count($query); $i < $count; $i++)
    {
        if( strlen($query[$i]) === 2)
        {
            $sql .= '(`admin_code1`) LIKE \'' . $query[$i] . '\'';
           
        }
        else
        {
            $sql .= 'MATCH (`place_name`, `postal_code`, `admin_name1`, `admin_code1`) AGAINST (\'' . $query[$i] . '\')';
            
            
        }
        if ($i < ($count - 1))
        {
            $sql .= ' AND ';
        }
    }
    $places = query($sql);
    
    // output places as JSON (pretty-printed for debugging convenience)
    header("Content-type: application/json");
    print(json_encode($places, JSON_PRETTY_PRINT));

?>
