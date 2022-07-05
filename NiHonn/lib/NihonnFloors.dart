import 'package:flutter/material.dart';
import 'dart:math';

import 'package:nihonn/NihonnNumbers.dart';

class NihonnFloors {
  static var floorElements = <String, String>{
    "1": "いっ",
    "2": "に",
    "3": "さん",
    "4": "よん",
    "5": "ご",
    "6": "ろっ",
    "7": "なな",
    "8": "はっ",
    "9": "きゅう",
    "10": "じゅっ",
    "20": "にじゅっ",
    "30": "さんじゅっ",
    "40": "よんじゅっ",
    "50": "ごじゅっ",
    "60": "ろくじゅっ",
    "70": "ななじゅっ",
    "80": "はちじゅっ",
    "90": "きゅうじゅっ",
  };
  var rnd = Random();
  var rndNumber = [0, 0];

  String nihonngo = "";
  String chinese = "";
  bool show = false;

  NihonnFloors() {
    rndNumber[0] = rnd.nextInt(9) + 1;
    rndNumber[1] = rnd.nextInt(10);
    chinese = "${rndNumber[0].toString()} ${rndNumber[1].toString()} 层";
    if (rndNumber[1] == 0) {
      nihonngo = "${floorElements[(rndNumber[0] * 10).toString()]} かい";
    } else {
      nihonngo = "${NihonnNumbers.numberElements[(rndNumber[0] * 10).toString()]} ${floorElements[rndNumber[1].toString()]} かい";
    }
  }
}

class NihonnFloorsListWidget extends StatefulWidget {
  const NihonnFloorsListWidget({Key? key}) : super(key: key);

  @override
  NihonnFloorsListState createState() => NihonnFloorsListState();
}

class NihonnFloorsListState extends State {
  List<NihonnFloors> items = List<NihonnFloors>.generate(100, (index) => NihonnFloors());

  @override
  Widget build(BuildContext context) {
    const title = "階（かい）";
    return MaterialApp(
      title: title,
      home: Scaffold(
        appBar: AppBar(
          title: const Text(title),
        ),
        body: ListView.builder(
          // Let the ListView know how many items it needs to build.
          itemCount: items.length,
          // Provide a builder function. This is where the magic happens.
          // Convert each item into a widget based on the type of item it is.
          itemBuilder: (context, index) {
            final item = items[index];

            return ListTile(
              title: Text(item.show ? "${item.chinese}\n${item.nihonngo}\n" : "${item.chinese}\n\n"),
              subtitle: const TextField(
                decoration: InputDecoration(
                  border: OutlineInputBorder(),
                  hintText: "Input Here",
                ),
              ),
              onTap: () {
                setState(() {
                  item.show = !item.show;
                });
              },
            );
          },
        ),
      ),
    );
  }
}
