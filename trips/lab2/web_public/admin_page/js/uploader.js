const resultContainer = document.getElementById("result_container");

/**
 * Created by WiskiW on 08.10.2017.
 */

const msgList = document.getElementById("msg_list");
const msgContainer = document.getElementById("msg_container");
const uploadButton = document.getElementById('upload_btn');
const saveButton = document.getElementById('save_btn');

const facSelectorElement = document.getElementById("fac_selector");
const courseSelectorElement = document.getElementById("course_selector");
const subgroupsSelectorElement = document.getElementById("subgroup_numb");

const FAC_LIST = {
    fit: 'ФИТ',
    gf: 'ГФ'
    /*,
    isf: 'ИСФ',
    mtf: 'МТФ',
    rtf: 'РТФ',
    fef: 'ФЭФ',
    juf: 'ЮФ'
    */
};

const FILENAME_PREFIX_LIST = {
    fit: ['fit'],
    gf: ['rgf', 'aja', 'rja', 'iff']
};

var file;

var fac = 'unset';
var course = 0;
var sgpg = 0;


document.getElementById("document").addEventListener("change", handleFileSelect, false);
predraw();

function predraw() {
    // Заполнение FAC селектора
    var number = 0;
    const facObj = new Option('Факультет', 'fac');
    facObj.setAttribute("style", "display:none");
    facSelectorElement.options[number] = facObj;
    number++;
    for (var facV in FAC_LIST) {
        var vacN = FAC_LIST[facV];
        facSelectorElement.options[number] = new Option(vacN, facV);
        number++;
    }
}

function sendFile() {
    uploadButton.setAttribute('disabled', 'true');
    readFileInputEventAsArrayBuffer(file, post);

    resultContainer.setAttribute("style", "display: none");
    clearSelector(msgList);
    msgContainer.innerHTML = '';
}

function parseFileName(filename) {
    const REG_EXP_FAC_COURSE = /[A-z-–]{2,}\s*[-–]\s*[1-6]/gi;
    const facCourseList = getByRegExp(filename, REG_EXP_FAC_COURSE);
    if (facCourseList.length === 1) {
        const facCourse = facCourseList[0];

        const courseStr = facCourse.charAt(facCourse.length - 1);
        const localCourse = parseInt(courseStr);
        if (!isNaN(course)) {
            course = localCourse;
            selectCourseByValue(course);
        } else {
            courseSelectorElement.value = 'course';
        }

        var filenamePrefix = facCourse.replace(/[-–]\s*[0-6]/gi, '');
        console.log('Filename prefix: ' + filenamePrefix);

        if (filenamePrefix !== undefined && filenamePrefix.trim() !== '') {
            filenamePrefix = filenamePrefix.toLowerCase().trim();
            selectFacByFileNamePrefix(filenamePrefix);
            subgroupsNumbByFileName(filenamePrefix, course);
        } else {
            facSelectorElement.value = 'fac'
        }
    }

    function selectFacByFileNamePrefix(filenamePrefix) {
        var lFac;
        var foundFacInList = '';

        // перебор по объекту с названиями файлов для факультетов
        for (lFac in FILENAME_PREFIX_LIST) {
            FILENAME_PREFIX_LIST[lFac].forEach(function (filename) {
                if (foundFacInList === '' && filenamePrefix === filename) {
                    fac = foundFacInList = lFac;
                }
            });
        }

        const list = facSelectorElement.options;
        if (foundFacInList === '') {
            facSelectorElement.value = list[0].value;
        } else {
            var i = 1; // т к первый элемент - Факультет
            // поиск нужного индекса для FacSelector
            for (lFac in FAC_LIST) {
                if (lFac === foundFacInList) {
                    console.log('Select fac by filename: %s', list[i].text);
                    facSelectorElement.value = list[i].value;
                    return;
                }
                i++;
            }
        }
    }

    function selectCourseByValue(courseValue) {
        const list = courseSelectorElement.options;
        for (var k = 0; k < list.length; k++) {
            if (list[k].value == courseValue) {
                console.log('Select course by filename: %d', k);
                courseSelectorElement.value = k;
                return;
            }
        }
        courseSelectorElement.value = 'course';
    }

    function subgroupsNumbByFileName(filenamePrefix, course) {
        for (var f in FILENAME_PREFIX_LIST) {
            if (FILENAME_PREFIX_LIST[f].includes(filenamePrefix)) {
                switch (f) {
                    case 'fit':
                    case'gf':
                        setSGPG(2);
                        return;
                }
            }
        }

        setSGPG(2);

        function setSGPG(v) {
            sgpg = v;
            subgroupsSelectorElement.value = v;
        }
    }

    function getByRegExp(source, exp) {
        const res = source.match(exp);
        if (res === null) {
            return [];
        } else {
            return res;
        }
    }
}


function handleFileSelect(event) {
    file = event.target.files[0];
    if (file !== undefined) {
        parseFileName(file.name);
    }
    enablePrefs();
}

function clearSelector(select) {
    while (select.options.length > 0) {
        select.remove(0);
    }
}

function enablePrefs() {
    const prefs = document.getElementsByClassName('pref');
    for (var i = 0; i < prefs.length; i++) {
        prefs [i].removeAttribute('disabled');
    }
    uploadButton.removeAttribute('disabled');
}


let jsonRes;

function processResult(res) {
    resultContainer.setAttribute("style", "display: block");
    const saveButton = document.getElementById('save_btn');
    saveButton.setAttribute('disabled', 'true');

    let completeText;

    jsonRes = JSON.parse(res);
    //console.log(res);

    clearSelector(msgList); // очистка стиля блока отображения ошибки
    msgContainer.removeAttribute('class'); // очистка списка ошибок

    if (jsonRes.logs !== undefined && jsonRes.logs.length > 0) {
        let criticalException = false;
        jsonRes.logs.forEach(function (log, k) {
            msgList.options[k] = new Option('[' + log.code + '] ' + log.displayText, k);
            msgList.options[k].classList.add(getLogClassStyle(log));

            if (Math.floor(log.code / 1000) === 3) { // если ошибка 3ххх
                criticalException = true;
            }
        });
        if (criticalException){
            completeText = 'Сканирование прервано: обнаружены критические ошибки!';
        } else {
            completeText = 'Сканирование успешно (найдено предупреждений: ' + jsonRes.logs.length + ')';
            saveButton.removeAttribute('disabled');
        }

        // отображение подробностей о первой ошибке
        msgList.value = 0;
        onChange(jsonRes.logs[0]);
        msgList.focus();
    } else {
        completeText  = 'Расписание успешно отсканировано';
        saveButton.removeAttribute('disabled');
    }

    msgList.addEventListener('change', function (ev) {
        // слушатель перехода по списку ошибок
        const json = jsonRes.logs[ev.target.value];
        onChange(json);
    });

    // обработчик отображения развернутой ошибки при переходе по списку
    function onChange(log) {
        let text = `[${log.code}] <strong>${log.displayText}</strong>: <i>${log.payload}</i></br>`;

        function getWhereProperty(key) {
            if (log.where.hasOwnProperty(key)) {
                return log.where[key];
            } else {
                return ''
            }
        }

        let prop;
        prop = getWhereProperty('weekDayIndex');
        if (prop !== '') {
            let dayOfWeek = prop;
            switch (prop) {
                case 0:
                    dayOfWeek = 'понедельник';
                    break;
                case 1:
                    dayOfWeek = 'вторник';
                    break;
                case 2:
                    dayOfWeek = 'среда';
                    break;
                case 3:
                    dayOfWeek = 'четверг';
                    break;
                case 4:
                    dayOfWeek = 'пятница';
                    break;
                case 5:
                    dayOfWeek = 'суббота';
                    break;
            }
            text = `${text}День недели: ${dayOfWeek.toUpperCase()}</br>`;
        }
        prop = getWhereProperty('subRow');
        if (prop !== '') {
            let weekColor = prop;
            switch (prop) {
                case 'a': // eng
                case 'а': // rus
                    weekColor = 'белая';
                    break;
                case 'b':
                    weekColor = 'зелёная';
            }
            text = `${text}Неделя: ${weekColor.toUpperCase()}</br>`;
        }
        prop = getWhereProperty('dayLessonIndex');
        if (prop !== '') {
            text = `${text}Номер пары: ${prop + 1}</br>`;
        }
        prop = getWhereProperty('rowTime');
        if (prop !== '') {
            const REG_EXP_TIME_CELL = /[0-9]{1,2}\s*:\s*[0-9]{2}/gi;
            function getByRegExp(source, exp) {
                const res = source.match(exp);
                if (res === null) {
                    return [];
                } else {
                    return res;
                }
            }

            const timeList = getByRegExp(prop, REG_EXP_TIME_CELL);
            if (timeList.length === 2) {
                const startTimeStr = timeList[0].replace(/\s*/g, '');
                const endTimeStr = timeList[1].replace(/\s*/g, '');
                prop = startTimeStr + " - " + endTimeStr;
            }

            text = `${text}Время: ${prop}</br>`;
        }


        let title;
        prop = getWhereProperty('tableRowIndex');
        if (prop !== '') {
            title = 'Строка: ' + prop + 1 + '\n';
        }
        prop = getWhereProperty('tableCellIndex');
        if (prop !== '') {
            title += 'Столбец: ' + prop + 1;
        }

        msgContainer.setAttribute('title', title);
        msgContainer.innerHTML = text;
        msgContainer.setAttribute('class', getLogClassStyle(log));
    }

    document.getElementById('complete_text').innerHTML = completeText;

    function getLogClassStyle(log) {
        switch (Math.floor(log.code / 1000)) {
            case 1:
                return 'option_info';
            case 2:
                return 'option_warning';
            case 3:
                return 'option_error';
            default:
                return 'option';
        }
    }
}

function saveToDatabase() {
    firebase.auth().onAuthStateChanged(function (user) {
        if (!user) {
            window.location.replace("./login.html");
            return;
        }
    });

    const xhr = new XMLHttpRequest();
    saveButton.setAttribute('disabled', 'true');
    xhr.onload = xhr.onerror = function () {
        saveButton.removeAttribute('disabled');
        if (xhr.status === 200) {
            alert("Расписание успешно опубликовано: " + xhr.responseText);
        } else {
            alert("Не удалось опубликовать расписание: " + xhr.responseText);
            console.log("error " + this.status);
        }
    };

    // если запуск с localhost, то запрос кидаем на локальный сервер, иначе - на firebase

    const hosting = document.location;
    if (hosting.host.includes("localhost") || hosting.origin.includes("file")) {
        // localhost
        xhr.open("POST", "http://localhost:3000/psu_saver", true);
    } else {
        // firebase hosting
        xhr.open('POST', 'https://us-central1-psu-by.cloudfunctions.net/psu_saver', true);
    }

    xhr.setRequestHeader('Content-Type', 'application/json');

    xhr.send(JSON.stringify({
        data: jsonRes.data,
        fac: fac,
        user: 'SomeUser', // TODO: Setup user name
        course: course
    }));
}

function post(result) {
    var xhr = new XMLHttpRequest();
    xhr.onload = xhr.onerror = function () {
        uploadButton.removeAttribute('disabled');
        if (xhr.status === 200) {
            //console.log(xhr.responseText);
            processResult(xhr.responseText);
        } else {
            console.log("error " + this.status);
        }
    };

    // если запуск с localhost, то запрос кидаем на локальный сервер, иначе - на firebase

    const hosting = document.location;
    if (hosting.host.includes("localhost") || hosting.origin.includes("file")) {
        // localhost
        xhr.open("POST", "http://localhost:3000/", true);
    } else {
        // firebase hosting
        xhr.open('POST', 'https://us-central1-psu-by.cloudfunctions.net/psu', true);
    }

    xhr.setRequestHeader('Content-Type', 'application/json');


    fac = facSelectorElement.options[facSelectorElement.selectedIndex].value;
    course = courseSelectorElement.options[courseSelectorElement.selectedIndex].value;
    sgpg = parseInt(subgroupsSelectorElement.value.trim());
    if (sgpg <= 0) {
        sgpg = 2;
    }

    var json = JSON.stringify({
        html: result.value,
        fac: fac,
        sgpg: sgpg,
        course: course
		//,action: "show"
    });

    xhr.send(json);
}


function readFileInputEventAsArrayBuffer(file, callback) {
    var reader = new FileReader();

    reader.onload = function (loadEvent) {
        var arrayBuffer = loadEvent.target.result;
        //console.log("result1: " + arrayBuffer);
        mammoth.convertToHtml({arrayBuffer: arrayBuffer})
            .then(callback)
            .done();
    };

    reader.readAsArrayBuffer(file);
}
