requirejs.config({
    baseUrl: "qrc:/js",
    paths: {
        home: "pages/home",
        console: "console",
        jquery: 'lib/jquery',
        highcharts: 'lib/highcharts',
        highcharts_canvas: 'pages/highcharts-canvas',
        heatmap: 'lib/modules/heatmap',
        constants: 'lib/constants',
        canvasjs: 'lib/canvasjs',
        exporting: 'lib/modules/exporting',
        exporting_offline: 'lib/modules/offline-exporting',
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
