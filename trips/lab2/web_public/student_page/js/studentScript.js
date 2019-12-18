const WEEK_WHITE = 'white';
const WEEK_GREEN = 'green';

const COOKIE_FAC = 'fuck';
const COOKIE_COURSE = 'course';
const COOKIE_GROUP = 'group';
const COOKIE_SUBGROUP = 'subgroup';

const KEY_DATA = 'data';
const KEY_INFO = 'info';

let week = WEEK_WHITE;
let fac = 'fit';
let course;
let group;
let subGroup;
let day = 1;

const borderElement = document.getElementById('color_border');

const facSelector = document.getElementById('fac_selector');
const courseSelector = document.getElementById('course_selector');
const groupSelector = document.getElementById('group_selector');
const subGroupSelector = document.getElementById('subgroup_selector');

const container = document.getElementById('schedule_container');
let databaseJson;

function setCookie(name, value) {
    value = encodeURIComponent(value);
    document.cookie = name + "=" + value;
}

function getCookie(name) {
    var matches = document.cookie.match(new RegExp(
        "(?:^|; )" + name.replace(/([\.$?*|{}\(\)\[\]\\\/\+^])/g, '\\$1') + "=([^;]*)"
    ));
    return matches ? decodeURIComponent(matches[1]) : undefined;
}

function deleteCookie(name) {
    setCookie(name, "")
}

function clearSelector(select) {
    while (select.options.length > 0) {
        select.remove(0);
    }
}

function selectOption(selectorElement, dataList, cookieTag, optionName) {
    let selectValue = undefined;
    if (dataList.length > 0) {
        clearSelector(selectorElement);
        dataList.forEach(function (keyStr, number) {
            selectorElement.options[number] = new Option(optionName(keyStr, number), keyStr);
        });
        const previewCookieValue = getCookie(cookieTag);
        if (previewCookieValue === undefined || selectOptionByValue(previewCookieValue) === -1) {
            selectValue = dataList[0];
        } else {
            selectValue = previewCookieValue;
        }
        setCookie(cookieTag, selectValue);
    } else {
        alert('ERROR: ' + cookieTag.toUpperCase() + ' list is empty!');
        throw 'Not enough data: ' + cookieTag;
    }
    return selectValue;

    function selectOptionByValue(value1) {
        const opts = selectorElement.options;
        for (let k = 0; k < opts.length; k++) {
            const opt = opts[k];
            if (opt.value === value1) {
                selectorElement.selectedIndex = k;
                return k;
            }
        }
        return -1;
    }
}

function fillFacSelector() {
    function getFacs() {
        const facList = [];
        const data = databaseJson.val();
        Object.keys(data).map(function (objectKey, index) {
            facList[index] = objectKey;
        });
        return facList;
    }

    const facList = getFacs();
    fac = selectOption(facSelector, facList, COOKIE_FAC,
        (keyStr, n) => keyStr.toUpperCase());
}

function fillCourseSelector() {
    function getCourses() {
        const courseList = [];
        const data = databaseJson.val()[fac];
        Object.keys(data).map(function (objectKey, index) {
            courseList[index] = objectKey;
        });
        return courseList;
    }

    const courseList = getCourses();
    course = selectOption(courseSelector, courseList, COOKIE_COURSE, (keyStr, n) => keyStr + ' курс');
}

function fillGroupsSelector() {
    function getGroups() {
        const groupList = [];
        const data = databaseJson.val()[fac][course][KEY_DATA];
        Object.keys(data).map(function (objectKey, index) {
            groupList[index] = objectKey;
        });
        return groupList;
    }

    const groupList = getGroups();
    group = selectOption(groupSelector, groupList, COOKIE_GROUP, (keyStr, n) => keyStr);
}

function fillSubGroupsSelector() {
    function getSubGroups() {
        const subgroupList = [];
        const data = databaseJson.val()[fac][course][KEY_DATA][group];
        Object.keys(data).map(function (objectKey, index) {
            subgroupList[index] = objectKey;
        });
        return subgroupList;
    }

    const subGroups = getSubGroups();
    subGroup = selectOption(subGroupSelector, subGroups, COOKIE_SUBGROUP,
        (keyStr, n) => keyStr + ' подгруппа');
}

function initButtonsListeners() {
    //(this.className=='week_button')?this.className='active_button':this.className='week_button';
    var buttons = document.querySelectorAll('.button');
    for (var i = 0; i < buttons.length; i++) {
        buttons[i].addEventListener('click', function () {
            const button = this;

            if (button.classList.contains('day_button')) {
                // обработка нажатий для кнопок дней недели
                day = button.getAttribute('day_index'); // сохранение нового значения

                // деактивация кнопок
                const dayButtons = document.querySelectorAll('.day_button');
                dayButtons.forEach(function (dayButton) {
                    dayButton.classList.remove('active_button');
                });

            } else if (button.classList.contains('color_button')) {
                // обработка нажатий для кнопок выбора цвета недели

                week = button.getAttribute('week_color'); // сохранение нового значения

                // деактивация кнопок
                const colorButtons = document.querySelectorAll('.color_button');
                colorButtons.forEach(function (colorButton) {
                    colorButton.classList.remove('active_button')
                });

                // смена цвета рамки
                /*
                if (week === WEEK_GREEN) {
                    borderElement.classList.add('border_green');
                    borderElement.classList.remove('border_white');
                } else {
                    borderElement.classList.remove('border_green');
                    borderElement.classList.add('border_white');
                }
                */
            }
            button.classList.toggle('active_button');
            onPropertyChange();
            //alert(button.className);
            //alert('k');
        });
    }
}

function initFacListener() {
    facSelector.addEventListener("change", function () {
        fac = this.value;
        setCookie(COOKIE_FAC, fac);
        deleteCookie(COOKIE_COURSE);
        deleteCookie(COOKIE_GROUP);
        deleteCookie(COOKIE_SUBGROUP);
        fillCourseSelector();
        fillGroupsSelector();
        fillSubGroupsSelector();
        onPropertyChange();
    });
}

function initCourseListener() {
    courseSelector.addEventListener("change", function () {
        course = this.value;
        setCookie(COOKIE_COURSE, course);
        deleteCookie(COOKIE_GROUP);
        deleteCookie(COOKIE_SUBGROUP);
        fillGroupsSelector();
        fillSubGroupsSelector();
        onPropertyChange();
    });
}

function initGroupListener() {
    groupSelector.addEventListener("change", function () {
        group = this.value;
        setCookie(COOKIE_GROUP, group);
        deleteCookie(COOKIE_SUBGROUP);
        fillSubGroupsSelector();
        onPropertyChange();
    });
}

function initSubGroupListener() {
    subGroupSelector.addEventListener("change", function () {
        subGroup = this.value;
        setCookie(COOKIE_SUBGROUP, subGroup);
        onPropertyChange();
    });
}

function onPropertyChange() {
    // обработчик изменений выбранных параметров
    tableCreate();
}

function tableCreate() {
    const scheduleJson = databaseJson.val()[fac][course][KEY_DATA][group][subGroup][week][day];

    const lessonKeyList = Object.keys(scheduleJson);

    var tbl = document.createElement('table');
    tbl.style.width = '100%';
    tbl.setAttribute('border', '1');
    var tbdy = document.createElement('tbody');
    for (var i = 0; i < lessonKeyList.length; i++) {
        var lessonObj = scheduleJson[lessonKeyList[i]];
        var tr = document.createElement('tr');
        for (var j = 0; j < 3; j++) {
            var td = document.createElement('td');
            switch (j) {
                case 0:
                    td.innerHTML = i + 1;
                    break;
                case 1:
                    td.innerHTML = getTimeText(lessonObj['time']);
                    break;
                case 2:
                    td.innerHTML = lessonObj['lesson'];
                    td.setAttribute('title', getLessonHint(lessonObj));
                    break;
            }
            //td.appendChild(document.createTextNode(cellText));
            tr.appendChild(td)
        }
        tbdy.appendChild(tr);
    }
    tbl.appendChild(tbdy);
    container.innerHTML = '';
    container.appendChild(tbl);

    function getTimeText(timeObj) {
        const startTimeMs = timeObj['startTime'];
        const endTimeMs = timeObj['endTime'];
        const startTime = new Date(startTimeMs);
        const endTime = new Date(endTimeMs);

        const startTimeHours = Math.floor(startTime.getHours() / 10) < 1 ? '0' + startTime.getHours() :
            startTime.getHours();
        const startTimeMinutes = Math.floor(startTime.getMinutes() / 10) < 1 ? '0' + startTime.getMinutes() :
            startTime.getMinutes();

        const endTimeHours = Math.floor(endTime.getHours() / 10) < 1 ? '0' + endTime.getHours() :
            endTime.getHours();
        const endTimeMinutes = Math.floor(endTime.getMinutes() / 10) < 1 ? '0' + endTime.getMinutes() :
            endTime.getMinutes();

        const string = startTimeHours + ':' + startTimeMinutes + '\n' + endTimeHours + ':' + endTimeMinutes;
        return string;
    }

    function getLessonHint(lessonObj) {
        const lessons = lessonObj['cellLesson'];
        if (lessons === undefined || lessons === '') {
            return '';
        }
        let string = '';

        for (let lessonIndex = 0; lessonIndex < lessons.length; lessonIndex++) {
            if (lessonIndex !== 0) {
                string = string + '==================== И ====================\n';
            }
            const lessonsForChoose = lessons[lessonIndex];
            for (let lessonForChooseIndex = 0;
                 lessonForChooseIndex < lessonsForChoose.length; lessonForChooseIndex++) {
                if (lessonForChooseIndex !== 0) {
                    string = string + '------------------- ИЛИ -------------------\n';
                }
                for (let key in lessonsForChoose[lessonForChooseIndex]) {
                    string = string + key + ': ' + lessonsForChoose[lessonForChooseIndex][key] + '\n';
                }
            }
        }

        string = string.replace(/\n+$/g, '');
        return string;
    }
}

function start() {

    loadSchedule().then(function (json) {
        databaseJson = json;

        fillFacSelector();
        fillCourseSelector();
        fillGroupsSelector();
        fillSubGroupsSelector();

        onPropertyChange();
    });
}


function chooseDay() {
    day = new Date().getDay();
    if (day < 1 || day > 6) {
        day = 1;
    }
    const list = document.getElementsByClassName('day_button');
    for (let i = 0; i < list.length; i++) {
        const el = list[i];
        if (el.getAttribute('day_index') === day + '') {
            el.classList.toggle('active_button');
            break;
        }
    }
}

function chooseWeek() {

    function getWeekNumber() {
        const c = new Date();
        const onejan = new Date(c.getFullYear(), 0, 1);
        return Math.ceil((((c - onejan) / 86400000) + onejan.getDay() + 1) / 7);
    }

    const weekNumber = getWeekNumber();
    /*
    if (weekNumber % 2 === 1) {
        week = WEEK_GREEN;
        borderElement.classList.add('border_green');
        borderElement.classList.remove('border_white');
    } else {
        week = WEEK_WHITE;
        borderElement.classList.remove('border_green');
        borderElement.classList.add('border_white');
    }
    */

    const list = document.getElementsByClassName('color_button');
    for (let i = 0; i < list.length; i++) {
        const el = list[i];
        if (el.getAttribute('week_color') === week) {
            el.classList.toggle('active_button');
            break;
        }
    }
}

chooseDay();
chooseWeek();

initButtonsListeners();
initFacListener();
initCourseListener();
initGroupListener();
initSubGroupListener();
