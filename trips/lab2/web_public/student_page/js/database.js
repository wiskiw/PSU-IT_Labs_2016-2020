// Get a reference to the database service
const database = firebase.database();


function loadSchedule() {
    return database.ref('/schedule/').once('value').then(function (snapshot) {
        //container.innerHTML = JSON.stringify(snapshot.val());
        database.goOffline();
        return snapshot;
    });
}