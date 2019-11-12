import 'react-hot-loader'
import 'normalize.css/normalize.css'
import '@blueprintjs/icons/lib/css/blueprint-icons.css'
import '@blueprintjs/core/lib/css/blueprint.css'
import '@electricui/components-desktop-blueprint/lib/bundle.css'
import './index.css'

import React from 'react'
import ReactDOM from 'react-dom'
import Root from './Root'
import { configureStore } from './state'
import { setupSettingsListenersApplication } from '@electricui/utility-electron'
require('@electricui/helpers')

// TODO: Figure out why the webpack env isn't taking
declare const module: any

setupSettingsListenersApplication()


let root = document.createElement('div')
root.className = 'root'
document.body.appendChild(root)

const store = configureStore()

function render(Component: any) {
  ReactDOM.render(<Component store={store} />, root)
}

render(Root)

if (module.hot) {
  module.hot.accept('./Root', () => {
    const NextRoot = require('./Root').default
    render(NextRoot)
  })
}