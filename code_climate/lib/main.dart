import 'package:flutter/material.dart';

void main() {
  runApp(const MyApp());
}

class MyApp extends StatelessWidget {
  const MyApp({super.key});

  // This widget is the root of your application.
  @override
  Widget build(BuildContext context) {
    return MaterialApp(
      title: 'Flutter Demo',
      theme: ThemeData(
        // This is the theme of your application.
        //
        // TRY THIS: Try running your application with "flutter run". You'll see
        // the application has a purple toolbar. Then, without quitting the app,
        // try changing the seedColor in the colorScheme below to Colors.green
        // and then invoke "hot reload" (save your changes or press the "hot
        // reload" button in a Flutter-supported IDE, or press "r" if you used
        // the command line to start the app).
        //
        // Notice that the counter didn't reset back to zero; the application
        // state is not lost during the reload. To reset the state, use hot
        // restart instead.
        //
        // This works for code too, not just values: Most code changes can be
        // tested with just a hot reload.
        colorScheme: ColorScheme.fromSeed(seedColor: Colors.deepPurple),
      ),
      home:  BadHomePage(),
    );
  }
}

class BadHomePage extends StatefulWidget {
  @override
  _BadHomePageState createState() => _BadHomePageState();
}

class _BadHomePageState extends State<BadHomePage> {
  int counter = 0;

  // ❌ Unused function (dead code)
  void neverUsedFunction() {
    print("I am never used");
  }

  @override
  Widget build(BuildContext context) {
    return Scaffold(
      appBar: AppBar(title: Text("Bad Code Example")),
      body: Column(
        children: [
          // ❌ Duplicated widget code
          Container(
            margin: EdgeInsets.all(16),
            padding: EdgeInsets.all(16),
            color: Colors.red,
            child: Text("Counter: $counter"),
          ),
          Container(
            margin: EdgeInsets.all(16),
            padding: EdgeInsets.all(16),
            color: Colors.red,
            child: Text("Counter: $counter"),
          ),

          // ❌ Long inline function
          ElevatedButton(
            onPressed: () {
              setState(() {
                counter++;
                if (counter % 2 == 0) {
                  counter = counter * 2;
                  if (counter > 10) {
                    counter = 1;
                  }
                }
              });
            },
            child: Text("Increase Counter"),
          ),
        ],
      ),
    );
  }
}
