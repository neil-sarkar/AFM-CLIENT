requirejs.config({
    baseUrl: "qrc:/js",
    paths: {
        home: "pages/home",
        console: "console",
        classnames: "lib/classNames",
        jquery: 'lib/jquery',
        highcharts: 'lib/highcharts',
        highcharts_canvas: 'pages/highcharts-canvas',
        boost: 'lib/modules/boost',
        heatmap: 'lib/modules/heatmap',
        underscore: 'lib/underscore',
        react: 'lib/react',
        dom: 'lib/react-dom',
        browser: 'lib/browser',
        JSXTransformer: "JSXTransformer",
        jsx: "jsx",
    },
    shim: {
    },
    jsx: {
        fileExtension: '.jsx'
    },
    name: "jsx!app",
});
