<!DOCTYPE html>
<html lang="en">

<script type="text/javascript">

    function validateName(form) {
        var val = form.elements["name"].value;
        return (val != null
            && val.trim() !== ""
            && (new RegExp('^\s*[A-ZА-ЯЁ]', 'gm').test(val)))
    }

    function validateYear(form) {
        var val = parseInt(form.elements["year"].value);
        return val > 0 && val <= 2018
    }

    function validateSize(form) {
        var val = parseInt(form.elements["size"].value);
        return val > 0
    }

    function validateAuthor(form) {
        var val = form.elements["author"].value;
        return (val != null
            && val.trim() !== ""
            && (new RegExp('^\s*[A-ZА-ЯЁ]', 'gm').test(val)))
    }


    function validate(form) {
        if (!validateName(form)) {
            alert("Bad book's name!");
            return false
        }

        if (!validateAuthor(form)) {
            alert("Bad author's name!");
            return false
        }

        if (!validateYear(form)) {
            alert("Bad year!");
            return false
        }

        if (!validateSize(form)) {
            alert("Bad book's size!");
            return false
        }
        return true
    }

</script>

<body>

<div class="center">
    <form title="Add Book" action="script.php" method="post" onsubmit="return validate(this)">
        <h3>Добавить книгу</h3>
        <table style="width:100%">
            <tr>
                <td>
                    <div>Название:</div>
                    <div id="name_err_container" class="err_message"></div>
                </td>
                <td><input title="Название книги" type="text" name="name"></td>
            </tr>
            <tr>
                <td>
                    <div>Автор:</div>
                    <div id="author_err_container" class="err_message"></div>
                </td>
                <td><input title="Автор книги" type="text" name="author"></td>
            </tr>
            <tr>
                <td>
                    <div>Год издания:</div>
                    <div id="year_err_container" class="err_message"></div>
                </td>
                <td><input title="Год издания" type="number" name="year"></td>
            </tr>
            <tr>
                <td>
                    <div>Количество страниц:</div>
                    <div id="size_err_container" class="err_message"></div>
                </td>
                <td><input title="Количество страниц" type="number" name="size"></td>
            </tr>
            <tr>
                <td colspan="2">
                    <input style="width: 100%" type="submit">
                </td>
            </tr>
        </table>
    </form>
</div>


</body>
<head>
    <meta charset="UTF-8">
    <title>Библиотека</title>
    <style>


        head {
            font-size: 22px;
        }

        .err_message {
            font-size: 14px;
            color: red;
            padding-left: 16px;
        }

        td {
            padding-top: 5px;
            padding-bottom: 5px;
        }

        input {
            width: 100%
        }

        .center {
            padding: 30px;
            margin: 0 auto;
            text-align: left;
            width: 800px;
            border: 3px solid #ad0b02;
        }
    </style>


</head>
</html>