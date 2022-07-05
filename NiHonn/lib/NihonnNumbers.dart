import 'package:flutter/material.dart';
import 'dart:math';

class NihonnNumbers {
  static var numberElements = <String, String>{
    "0": "れい／ぜろ",
    "1": "いち",
    "2": "に",
    "3": "さん",
    "4": "し／よん",
    "5": "ご",
    "6": "ろく",
    "7": "しち／なな",
    "8": "はち",
    "9": "く／きゅう",
    "10": "じゅう",
    "20": "にじゅう",
    "30": "さんじゅう",
    "40": "よんじゅう",
    "50": "ごじゅう",
    "60": "ろくじゅう",
    "70": "ななじゅう",
    "80": "はちじゅう",
    "90": "きゅうじゅう",
    "100": "ひゃく",
    "200": "にひゃく",
    "300": "さんびゃく",
    "400": "よんひゃく",
    "500": "ごひゃく",
    "600": "ろっぴゃく",
    "700": "ななひゃく",
    "800": "はっぴゃく",
    "900": "きゅうびゃく",
    "1000": "せん",
    "2000": "にせん",
    "3000": "さんぜん",
    "4000": "よんせん",
    "5000": "ごせん",
    "6000": "ろくせん",
    "7000": "ななせん",
    "8000": "はっせん",
    "9000": "きゅうせん",
    "10000": "いちまん",
    "100000": "じゅうまん",
    "1000000": "ひゃくまん",
    "10000000": "いっせんまん",
    "100000000": "いちおく",
    "十": "じゅう",
    "百": "ひゃく",
    "千": "せん",
    "万": "まん",
    "亿": "おく",
    ".": "てん"
  };
  var rnd = Random();
  var rndNumber = [0, 0, 0, 0];

  String nihonngo = "";
  String chinese = "";
  bool show = false;

  NihonnNumbers() {
    for (int i = 0; i < 4; i++) {
      rndNumber[i] = i == 0 ? rnd.nextInt(9) + 1 : rnd.nextInt(10);
      chinese = chinese + rndNumber[i].toString();
    }
    nihonngo =
        "${numberElements[(rndNumber[0] * 1000).toString()]!}  ${rndNumber[1] == 0 ? "" : numberElements[(rndNumber[1] * 100).toString()]!}  ${rndNumber[2] == 0 ? "" : numberElements[(rndNumber[2] * 10).toString()]!}  ${rndNumber[3] == 0 ? "" : numberElements[(rndNumber[3]).toString()]!}";
  }
}

class NihonnNumbersListWidgetStateless extends StatelessWidget{
  const NihonnNumbersListWidgetStateless({Key? key}) : super(key: key);

  @override
  Widget build(BuildContext context) {
    const title = "数字（すうじ）";
    return Scaffold(
      appBar: AppBar(
        title: const Text(title),
      ),
      body: ListView.builder(
        // Let the ListView know how many items it needs to build.
        itemCount: NihonnNumbers.numberElements.length,
        // Provide a builder function. This is where the magic happens.
        // Convert each item into a widget based on the type of item it is.
        itemBuilder: (context, index) {
          return ListTile(
            title: Text(NihonnNumbers.numberElements.values.elementAt(index)),
            subtitle: Text(NihonnNumbers.numberElements.keys.elementAt(index)),
          );
        },
      ),
    );
  }
}

class NihonnNumbersListWidget extends StatefulWidget {
  const NihonnNumbersListWidget({Key? key}) : super(key: key);

  @override
  NihonnNumbersListState createState() => NihonnNumbersListState();
}

class NihonnNumbersListState extends State {
  List<NihonnNumbers> items = List<NihonnNumbers>.generate(100, (index) => NihonnNumbers());

  @override
  Widget build(BuildContext context) {
    const title = "数字（すうじ）";
    return Scaffold(
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
    );
  }
}
