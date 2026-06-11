export const INSTRUMENTS = [
    { key: 'bombo', name: 'Bombo', prefix: '/kick/' },
    { key: 'caja', name: 'Caja', prefix: '/snare/' },
    { key: 'platillos', name: 'Platillos', prefix: '/hat/' },
    { key: 'bajo', name: 'Bajo WG', prefix: '/bass/' },
    { key: 'psycho', name: 'Synth Psyche', prefix: '/syn1/' },
    { key: 'siringe', name: 'Siringe FDN', prefix: '/syn2/' }
];

export class SequencerState {
    constructor() {
        this.playheadStep = -1;
        this.running = false;
        this.currentBpm = 140;
    }
}
