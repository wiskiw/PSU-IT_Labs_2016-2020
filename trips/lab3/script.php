<?php
/**
 * Created by PhpStorm.
 * User: wiskiw
 * Date: 27.04.18
 * Time: 1:22
 */
?>


<html>
    <body>

        <?php
        const FILE_NAME = "database.txt";

        $name = $_POST["name"];
        $author = $_POST["author"];
        $size = $_POST["size"];
        $year = $_POST["year"];

        function toString() {
            global $name;
            global $author;
            global $size;
            global $year;
            return "'$name' $author ($size) $year";
        }

        function fileContains($data) {
            return (strpos(file_get_contents(FILE_NAME), $data) !== false);
        }

        function save($data){
            file_put_contents(FILE_NAME, $data, FILE_APPEND | LOCK_EX);
        }

        $str = toString();
        if (!fileContains($str)) {
            save($str . "\n")
            ?>
            <h3>Книга добавлена!</h3>

            Книга: <?php echo "\"". $name . "\" от " . $author?><br/>
            Страниц: <?php echo $size?> <br/>
            Издана(год): <?php echo $year?><br/>
            <br/><a href="index.php">Добавить ещё</a>
            <?php
        } else {
            ?>
            <h3>Книга уже существует!</h3>
            <br/><a href="index.php">Добавить другую</a>
            <?php
        }
        ?>


    </body>
</html>