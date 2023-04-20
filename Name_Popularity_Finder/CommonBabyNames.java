/**********************************************
 Workshop #6
 Course: JAC444 - Fall Semester
 Last Name: Yakubov
 First Name: Lion
 ID: 129517207
 Section: NCC
 This assignment represents my own work in accordance with Seneca Academic Policy.
 Signature
 Date:10-11-2022
 **********************************************/
package com.example.demo;

import javafx.application.Application;
import javafx.application.Platform;
import javafx.geometry.HPos;
import javafx.geometry.Pos;
import javafx.scene.Scene;
import javafx.scene.control.Button;
import javafx.scene.control.Label;
import javafx.scene.control.TextField;
import javafx.scene.layout.GridPane;
import javafx.stage.Stage;

import java.io.*;
import java.util.Scanner;

public class CommonBabyNames extends Application{

    Button exit = new Button("Exit");
    Button submit = new Button("Submit Details");

    @Override
    public void start(Stage primaryStage) throws IOException {

        GridPane layout = new GridPane();
        layout.setVgap(25);
        Scene scene = new Scene(layout);
        layout.setAlignment(Pos.TOP_CENTER);

        Label yearLabel = new Label("Enter the year:");
        layout.add(yearLabel, 0, 1);
        GridPane.setHalignment(yearLabel, HPos.LEFT);
        TextField year = new TextField();
        layout.add(year, 1, 1);
        GridPane.setHalignment(year, HPos.LEFT);

        Label genderLabel = new Label("Enter the Gender (F/M): ");
        GridPane.setHalignment(genderLabel, HPos.LEFT);
        layout.add(genderLabel, 0, 2);
        TextField gender = new TextField();
        layout.add(gender, 1, 2);

        Label nameLabel = new Label("Enter the name: ");
        GridPane.setHalignment(nameLabel, HPos.LEFT);
        layout.add(nameLabel, 0, 3);
        TextField nameF = new TextField();
        layout.add(nameF, 1, 3);

        GridPane.setHalignment(submit, HPos.CENTER);
        layout.add(submit, 0, 4);
        submit.setOnAction(event -> {
            boolean valid = true;
            if(year.getText().matches("[0-9]*")){
                if(Integer.parseInt(year.getText()) > 2018 || Integer.parseInt(year.getText()) < 2009){
                    year.setText("2009-2018 only");
                    valid = false;
                }
            }
            else{
                year.setText("please enter a number");
                valid = false;
            }

            if(!gender.getText().toUpperCase().equals("M") && !gender.getText().toUpperCase().equals("F")){
                gender.setText("M/F");
                valid = false;
            }

            if(valid) {
                File nameFile = new File("C:\\Users\\Lion\\Desktop\\CPP\\Semester 4\\JAC444\\WS6\\babynames\\babynamesranking" + year.getText() + ".txt");
                try{
                    Scanner scf = new Scanner(nameFile);
                    String name = nameF.getText();
                    boolean found = false;
                    int rank = 0;
                    while(scf.hasNextLine() && !found){
                        String nameLine = scf.nextLine();
                        if(nameLine.contains(name)){
                            found = true;
                            rank = Integer.parseInt(nameLine.substring(0, nameLine.indexOf("\t")));
                            nameLine = nameLine.replace(nameLine.substring(0, nameLine.indexOf("\t") + 1), "");
                            String mName = nameLine.substring(0, nameLine.indexOf("\t"));
                            nameLine = nameLine.replace(nameLine.substring(0, nameLine.indexOf("\t") + 1), "");
                            String mNameNum = nameLine.substring(0, nameLine.indexOf("\t"));
                            nameLine = nameLine.replace(nameLine.substring(0, nameLine.indexOf("\t") + 1), "");
                            String fName = nameLine.substring(0, nameLine.indexOf("\t"));
                            nameLine = nameLine.replace(nameLine.substring(0, nameLine.indexOf("\t") + 1), "");
                            String fNameNum = nameLine;
                            if(gender.getText().equals("M") && !mName.equals(name)){
                                found = false;
                            }
                            else if(gender.getText().equals("F") && !fName.equals(name)){
                                found = false;
                            }
                        }
                    }
                    scf.close();

                    GridPane resultLayout = new GridPane();
                    Scene resultScene = new Scene(resultLayout);
                    Button restart = new Button("Yes");
                    Label result = new Label();
                    Label toRestart = new Label();
                    resultLayout.setVgap(20);
                    resultLayout.setAlignment(Pos.TOP_CENTER);
                    restart.setPrefWidth(100);

                    if(!found){
                        result.setText("Couldn't find the name in the list");
                    }
                    else{
                        if(gender.getText().equals("M")){
                            result.setText("Boy name " + name + " is ranked #" + rank + " in " + year.getText() + " year");
                        }
                        else{
                            result.setText("Girl name " + name + " is ranked #" + rank + " in " + year.getText() + " year");
                        }
                    }
                    toRestart.setText("Do you want to search another name?");
                    resultLayout.add(result, 0, 2);
                    resultLayout.add(toRestart,0, 4);
                    resultLayout.add(restart,0,5);
                    resultLayout.add(exit,1,5);
                    restart.setOnAction(restartEvent -> {
                        exit.setText("Exit");
                        layout.add(exit, 1, 4);
                        primaryStage.setScene(scene);
                    });
                    exit.setText("No");

                    primaryStage.setScene(resultScene);


                }
                catch(FileNotFoundException e){
                    System.out.println("Something went wrong, file not found.");
                }
            }
        });

        GridPane.setHalignment(exit, HPos.CENTER);
        exit.setPrefWidth(100);
        layout.add(exit, 1, 4);
        exit.setOnAction(event -> Platform.exit());

        primaryStage.setTitle("Search Name Ranking Application");
        primaryStage.setScene(scene);
        primaryStage.setWidth(400);
        primaryStage.setHeight(260);
        primaryStage.show();
    }

    public static void main(String[] args) {
        launch();
    }
}
