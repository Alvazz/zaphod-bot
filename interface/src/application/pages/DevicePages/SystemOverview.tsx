import {
  Button,
  ProgressBar,
  Statistic,
  Statistics,
} from '@electricui/components-desktop-blueprint'
import {
  CONTROL_MODES,
  SUPERVISOR_STATES,
} from '../../../transport-manager/config/codecs'
import { Divider, HTMLTable } from '@blueprintjs/core'

import {
  IntervalRequester,
  StateTree,
  useHardwareState,
} from '@electricui/components-core'

import { Composition } from 'atomic-layout'
import { Printer } from '@electricui/components-desktop'
import React from 'react'

const SupervisorState = () => {
  const supervisor_state = useHardwareState(state => state.super.supervisor)
  const is_moving = useHardwareState(state => state.moStat.pathing_state)

  let supervisor_text: string = 'null'

  if (supervisor_state === SUPERVISOR_STATES[SUPERVISOR_STATES.ARMED]) {
    if (is_moving == 1) {
      supervisor_text = 'MOVING'
    } else {
      supervisor_text = 'ARMED'
    }
  } else {
    supervisor_text = supervisor_state || 'UNKNOWN'
  }

  return <div>{supervisor_text}</div>
}

const ArmControlButton = () => {
  const supervisor = useHardwareState<string>(state => state.super.supervisor)
  const control_mode = useHardwareState(state => state.super.mode)

  const modeNotSelected = control_mode === CONTROL_MODES[CONTROL_MODES.NONE]
  const isArmed = supervisor === SUPERVISOR_STATES[SUPERVISOR_STATES.ARMED]

  if (!isArmed) {
    if (modeNotSelected) {
      return (
        <Button fill large disabled intent="none" callback="disarm">
          Select a mode before arming
        </Button>
      )
    } else {
      return (
        <Button fill large intent="warning" callback="arm">
          Arm ({control_mode})
        </Button>
      )
    }
  }

  return (
    <Button fill large intent="primary" callback="disarm">
      Disarm
    </Button>
  )
}

const systemOverviewAreas = `
RobotMode PositionOutput
ArmButton HomeButton
`

const SystemOverview = () => {
  const control_mode = useHardwareState(state => state.super.mode)

  const x_position = useHardwareState(state => state.cpos[0]) / 1000
  const y_position = useHardwareState(state => state.cpos[1]) / 1000
  const z_position = useHardwareState(state => state.cpos[2]) / 1000

  return (
    <div>
      <IntervalRequester variables={['cpos']} interval={50} />
      <Composition areas={systemOverviewAreas} gutter={20}>
        {Areas => (
          <>
            <Areas.RobotMode>
              <Statistics>
                <Statistic
                  value={<SupervisorState />}
                  label={<div>{control_mode} MODE</div>}
                />
              </Statistics>
            </Areas.RobotMode>
            <Areas.PositionOutput>
              <HTMLTable condensed style={{ minWidth: '100%' }}>
                <tbody>
                  <tr>
                    <td>X</td>
                    <td>{x_position.toFixed(2)} mm</td>
                  </tr>
                  <tr>
                    <td>Y</td>
                    <td>{y_position.toFixed(2)} mm</td>
                  </tr>
                  <tr>
                    <td>Z</td>
                    <td>{z_position.toFixed(2)} mm</td>
                  </tr>
                </tbody>
              </HTMLTable>
            </Areas.PositionOutput>
            <Areas.HomeButton>
              <Button fill large intent="success" callback="home">
                Home
              </Button>
            </Areas.HomeButton>
            <Areas.ArmButton>
              <ArmControlButton />
            </Areas.ArmButton>
          </>
        )}
      </Composition>
    </div>
  )
}

export default SystemOverview
