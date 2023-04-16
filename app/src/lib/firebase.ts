// Import the functions you need from the SDKs you need
import { deleteApp, getApp, getApps, initializeApp } from "firebase/app";
// import { getAnalytics } from "firebase/analytics";
import { getAuth } from "firebase/auth";
import { getDatabase } from "firebase/database";

// TODO: Add SDKs for Firebase products that you want to use
// https://firebase.google.com/docs/web/setup#available-libraries

// Your web app's Firebase configuration
// For Firebase JS SDK v7.20.0 and later, measurementId is optional
const firebaseConfig = {
  apiKey: "AIzaSyAQGxZdMZAZaCtUIZ8iTPLlrE8jbfR73e4",
  authDomain: "sensors-82505.firebaseapp.com",
  databaseURL: "https://sensors-82505-default-rtdb.europe-west1.firebasedatabase.app",
  projectId: "sensors-82505",
  storageBucket: "sensors-82505.appspot.com",
  messagingSenderId: "988668510469",
  appId: "1:988668510469:web:d8af30a7365556ee34776c",
  measurementId: "G-V8W494YYYE"
};

// Initialize Firebase
// Initialize Firebase
let firebaseApp;
if (!getApps().length) {
    firebaseApp = initializeApp(firebaseConfig)
} else {
    firebaseApp = getApp()
    deleteApp(firebaseApp)
    firebaseApp = initializeApp(firebaseConfig)
}

export const auth = getAuth(firebaseApp)
//check if is browser
// if (typeof window !== 'undefined') {
//     const analytics = getAnalytics(app);
// }
// const db = getDatabase();
// function getUser(){
//     return auth.currentUser;
// }
// export { db, getUser };
